module;

#include <string_view>
#include <string>
#include <functional>

export module UI.Page;

import UI.PageBuilder;


namespace tatzel {


export
class Page
{
public:
	Page(
		std::string_view route_path,
		std::function<void( PageBuilder<ui::LogicalElement> )>&& page_builder_fn
	);
	Page( const Page& ) = delete;
	Page( Page&& ) = default;
	~Page() = default;

	auto operator=( const Page& ) -> Page& = delete;
	auto operator=( Page&& ) -> Page& = default;

	std::string route_path;
	std::function<void( PageBuilder<ui::LogicalElement> )> page_builder_fn;
};


}
