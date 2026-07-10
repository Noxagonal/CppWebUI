module;

#include <string>
#include <string_view>
#include <functional>

export module UI.Page;

import UI.PageBuilder;


namespace ui {


export
class Page
{
public:
	Page(
		std::string_view route_path,
		std::function<void( PageBuilder<dom::Element> )>&& page_builder_fn
	);
	Page( const Page& ) = delete;
	Page( Page&& ) = default;
	~Page() = default;

	auto operator=( const Page& ) -> Page& = delete;
	auto operator=( Page&& ) -> Page& = default;

	std::string route_path;
	std::function<void( PageBuilder<dom::Element> )> page_builder_fn;
};


}
