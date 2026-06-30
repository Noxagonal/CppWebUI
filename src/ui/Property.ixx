module;

#include <functional>

export module UI.Property;


namespace ui {


export
template<typename T>
class Property
{
public:

	auto OnGet( std::function<void()>&& callback ) -> void
	{
		on_get_callbacks.push_back( std::move( callback ) );
	}

	auto OnSet( std::function<void(const T&)>&& callback ) -> void
	{
		on_set_callbacks.push_back( std::move( callback ) );
	}

	operator T&()
	{
		for( auto& callback : on_get_callbacks ) callback();
		return value;
	}

	auto operator=( const T& in )
	{
		value = in;
		for( auto& callback : on_set_callbacks ) callback( in );
	}

private:
	T value;
	std::vector<std::function<void()>> on_get_callbacks;
	std::vector<std::function<void(const T&)>> on_set_callbacks;
};


}