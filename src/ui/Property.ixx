module;

#include <string>
#include <string_view>
#include <functional>

export module UI.Property;


namespace ui {


export
template<typename T>
class ReadOnlyProperty
{
public:

	ReadOnlyProperty() = default;

	// Initial setup allowed.
	ReadOnlyProperty( const T& in )
	{
		this->value = in;
	}

	ReadOnlyProperty( std::string_view in ) requires( std::same_as<T, std::string> )
	{
		this->value = std::string{ in };
	}

	template<size_t StringLiteralLength>
	ReadOnlyProperty( const char(&in)[ StringLiteralLength ] ) requires( std::same_as<T, std::string> )
	{
		static_assert( StringLiteralLength > 0 );
		this->value = std::string{ in, StringLiteralLength - 1 };
	}

	ReadOnlyProperty( const ReadOnlyProperty& ) = delete;
	ReadOnlyProperty( ReadOnlyProperty&& ) = default;

	auto operator=( const ReadOnlyProperty& ) -> ReadOnlyProperty& = delete;
	auto operator=( ReadOnlyProperty&& ) -> ReadOnlyProperty& = default;

	auto OnGet( std::function<void()>&& callback ) -> void
	{
		this->on_get_callbacks.push_back( std::move( callback ) );
	}

	auto operator==( const T& other ) const -> bool requires( !std::same_as<T, std::string> )
	{
		return this->value == other;
	}

	auto operator==( std::string_view other ) const -> bool requires( !std::same_as<T, std::string> )
	{
		return this->value == other;
	}

	auto operator->() const -> const T requires( std::is_pointer_v<T> )
	{
		return this->value;
	}

	auto operator*() const -> const T& requires( std::is_pointer_v<T> )
	{
		return *this->value;
	}

	operator const T&()
	{
		this->RunGetCallbacks();
		return this->value;
	}

	operator std::string_view() requires( std::same_as<T, std::string> )
	{
		this->RunGetCallbacks();
		return this->value;
	}

	auto operator=( const T& in ) -> ReadOnlyProperty& = delete;

protected:
	T value;

private:
	auto RunGetCallbacks() -> void
	{
		for( auto& callback : this->on_get_callbacks ) callback();
	}

	std::vector<std::function<void()>> on_get_callbacks;
};


export
template<typename T>
class Property : public ReadOnlyProperty<T>
{
public:

	using ReadOnlyProperty<T>::ReadOnlyProperty;

	auto operator=( const Property& ) -> Property& = delete;
	auto operator=( Property&& ) -> Property& = default;

	auto OnSet( std::function<void(const T&)>&& callback ) -> void
	{
		this->on_set_callbacks.push_back( std::move( callback ) );
	}

	auto operator=( const T& in )
	{
		this->value = in;
		this->RunSetCallbacks( in );
	}

private:
	auto RunSetCallbacks( const T& in ) -> void
	{
		for( auto& callback : this->on_set_callbacks ) callback( in );
	}

	std::vector<std::function<void( const T& )>> on_set_callbacks;
};


}
