module;

#include <type_traits>
#include <functional>
#include <vector>
#include <string>
#include <string_view>

export module UI.Property;


namespace tatzel {


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

	ReadOnlyProperty( T&& in ) :
		value{ std::move( in ) }
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

	auto operator=( const T& in ) -> ReadOnlyProperty& = delete;
	auto operator=( T&& in ) -> ReadOnlyProperty& = delete;

	auto OnGet( std::function<void()> callback ) -> void
	{
		this->on_get_callbacks.push_back( std::move( callback ) );
	}

	auto operator==( const T& other ) const -> bool requires( !std::same_as<T, std::string> )
	{
		return this->Get() == other;
	}

	auto operator==( std::string_view other ) const -> bool requires( std::same_as<T, std::string> )
	{
		return this->Get() == other;
	}

	template<size_t StringLiteralLength>
	auto operator==( const char(&other)[ StringLiteralLength ] ) const -> bool requires( std::same_as<T, std::string> )
	{
		static_assert( StringLiteralLength > 0 );
		return this->Get() == std::string_view{ other, StringLiteralLength - 1 };
	}

	auto operator->() const -> const PointeeT* requires( std::is_pointer_v<T> )
	{
		return this->Get();
	}

	auto operator*() const -> const std::remove_pointer_t<T>& requires( std::is_pointer_v<T> )
	{
		return *this->Get();
	}

	operator const T&() const requires( !std::is_pointer_v<T> )
	{
		return this->Get();
	}

	operator std::string_view() const requires( std::same_as<T, std::string> )
	{
		return this->Get();
	}

protected:

	auto Get() const -> const T&
	{
		this->RunGetCallbacks();
		return value;
	}

	auto RunGetCallbacks() const -> void
	{
		const auto callback_count = this->on_get_callbacks.size();
		for( size_t index = 0; index < callback_count; ++index )
		{
			auto callback = this->on_get_callbacks[ index ];
			callback();
		}
	}

	T value;
	std::vector<std::function<void()>> on_get_callbacks;
};


export
template<typename T>
class Property : public ReadOnlyProperty<T>
{
protected:

	using PointeeT = typename ReadOnlyProperty<T>::PointeeT;

public:

	using ReadOnlyProperty<T>::ReadOnlyProperty;

	using ReadOnlyProperty<T>::operator->;
	using ReadOnlyProperty<T>::operator*;

	auto operator=( const Property& ) -> Property& = delete;
	auto operator=( Property&& ) -> Property& = default;

	auto OnSet( std::function<void(const T&)> callback ) -> void
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

	auto operator=( T&& in ) -> Property&
	{
		this->Set( std::move( in ) );
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

	auto Get() const -> T&
	{
		this->RunGetCallbacks();
		return this->value;
	}

	auto Set( const T& in ) -> void
	{
		this->value = in;
		this->RunSetCallbacks();
	}

	auto Set( T&& in ) -> void
	{
		this->value = std::move( in );
		this->RunSetCallbacks();
	}

	auto RunSetCallbacks() const -> void
	{
		const auto callback_count = this->on_set_callbacks.size();
		for( size_t index = 0; index < callback_count; ++index )
		{
			auto callback = this->on_set_callbacks[ index ];
			callback( this->value );
		}
	}

	std::vector<std::function<void( const T& )>> on_set_callbacks;
};


}
