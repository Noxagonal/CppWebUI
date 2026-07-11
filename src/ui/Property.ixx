module;

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
		// Set initial value;
		this->value = in;
	}

	explicit ReadOnlyProperty( const ReadOnlyProperty& ) = delete;
	explicit ReadOnlyProperty( ReadOnlyProperty&& ) = default;

	auto operator=( const ReadOnlyProperty& ) -> ReadOnlyProperty& = delete;
	auto operator=( ReadOnlyProperty&& ) -> ReadOnlyProperty& = default;

	auto OnGet( std::function<void()>&& callback ) -> void
	{
		this->on_get_callbacks.push_back( std::move( callback ) );
	}

	operator const T&()
	{
		for( auto& callback : this->on_get_callbacks ) callback();
		return this->value;
	}

	auto operator=( const T& in ) = delete;

protected:
	T value;

private:
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
		for( auto& callback : this->on_set_callbacks ) callback( in );
	}

private:
	std::vector<std::function<void(const T&)>> on_set_callbacks;
};


}
