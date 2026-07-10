module;

#include <string_view>
#include <functional>

module UI.Page;

import UI.DOM.Element;


ui::Page::Page(
	std::string_view route_path,
	std::function<void( PageBuilder<dom::Element> )>&& page_builder_fn
) :
	route_path( route_path ),
	page_builder_fn( std::move( page_builder_fn ) )
{}
