module;

#include <drogon/drogon.h>
#include "drogon/HttpAppFramework.h"

#include <string_view>
#include <functional>

export module UI.App;

import UI.Page;
import UI.PageBuilder;


namespace ui {


export
class App
{
public:
	App();
	App( const App& ) = delete;
	App( App&& ) = default;
	~App();

	auto operator=( const App& ) -> App& = delete;
	auto operator=( App&& ) -> App& = default;

	auto RegisterPage( std::string_view route_path, std::function<void( PageBuilder<dom::Element> )>&& page_builder_fn ) -> void;
	auto FindRegisteredPage( std::string_view route_path ) -> Page*;

	auto Run() -> void;

private:

	std::vector<Page> registered_page_list;
};


export
auto GetGlobalApp() -> App&;


}
