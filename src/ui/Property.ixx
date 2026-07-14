module;

#include <string>
#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>
#include <vector>
#include <functional>

export module UI.Property;


namespace ui {


export
template<typename T>
class ReadOnlyProperty
{
protected:

	using PointeeT = std::remove_pointer_t<T>;

public:

	ReadOnlyProperty() = default;

	// Initial setup allowed.
	ReadOnlyProperty( const T& in ) :
		value{ in }
	{}

	ReadOnlyProperty( std::string_view in ) requires( std::same_as<T, std::string> ) :
		value{ std::string{ in } }
	{}

	template<size_t StringLiteralLength>
	ReadOnlyProperty( const char(&in)[ StringLiteralLength ] ) requires( std::same_as<T, std::string> ) :
		value{ std::string{ in, StringLiteralLength - 1 } }
	{
		static_assert( StringLiteralLength > 0 );
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

	auto operator==( std::string_view other ) const -> bool requires( std::same_as<T, std::string> )
	{
		return this->value == other;
	}

	template<size_t StringLiteralLength>
	auto operator==( const char(&other)[ StringLiteralLength ] ) const -> bool requires( std::same_as<T, std::string> )
	{
		static_assert( StringLiteralLength > 0 );
		return this->value == std::string_view{ other, StringLiteralLength - 1 };
	}

	auto operator->() const -> const PointeeT* requires( std::is_pointer_v<T> )
	{
		return this->Get();
	}

	auto operator*() const -> const std::remove_pointer_t<T>& requires( std::is_pointer_v<T> )
	{
		return *this->Get();
	}

	operator const T&()
	{
		return this->Get();
	}

	operator std::string_view() requires( std::same_as<T, std::string> )
	{
		return this->Get();
	}

	auto operator=( const T& in ) -> ReadOnlyProperty& = delete;

protected:

	auto Get() const -> const T&
	{
		this->RunGetCallbacks();
		return value;
	}

	auto RunGetCallbacks() const -> void
	{
		for( auto& callback : this->on_get_callbacks ) callback();
	}

	T value;
	std::vector<std::function<void()>> on_get_callbacks;
};


export
template<typename T>
class Property : public ReadOnlyProperty<T>
{
protected:

	using PointeeT = ReadOnlyProperty<T>::PointeeT;

public:

	using ReadOnlyProperty<T>::ReadOnlyProperty;

	auto operator=( const Property& ) -> Property& = delete;
	auto operator=( Property&& ) -> Property& = default;

	auto OnSet( std::function<void(const T&)>&& callback ) -> void
	{
		this->on_set_callbacks.push_back( std::move( callback ) );
	}

	auto operator->() -> PointeeT* requires( std::is_pointer_v<T> )
	{
		return this->Get();
	}

	auto operator*() -> std::remove_pointer_t<T>& requires( std::is_pointer_v<T> )
	{
		return *this->Get();
	}

	operator T&()
	{
		return this->Get();
	}

	auto operator=( const T& in ) -> Property&
	{
		this->Set( in );
		return *this;
	}

	auto operator=( std::string_view in ) -> Property& requires( std::same_as<T, std::string> )
	{
		this->Set( std::string{ in } );
		return *this;
	}

	template<size_t StringLiteralLength>
	auto operator=( const char(&in)[ StringLiteralLength ] ) -> Property& requires( std::same_as<T, std::string> )
	{
		static_assert( StringLiteralLength > 0 );
		this->Set( std::string{ in, StringLiteralLength - 1 } );
		return *this;
	}

private:

	auto Get() -> T&
	{
		this->RunGetCallbacks();
		return this->value;
	}

	auto Set( const T& in ) -> void
	{
		this->value = in;
		this->RunSetCallbacks();
	}

	auto RunSetCallbacks() const -> void
	{
		for( auto& callback : this->on_set_callbacks ) callback( this->value );
	}

	std::vector<std::function<void( const T& )>> on_set_callbacks;
};


}
