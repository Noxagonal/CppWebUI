module;

#include <drogon/drogon.h>
#include "drogon/HttpAppFramework.h"

module UI.App;

import UI.Utility;


ui::App* global_app = nullptr;


ui::App::App()
{
	drogon::app().loadConfigFile( "./data/drogon_config.json" );
	if( global_app ) throw std::runtime_error{ "Global app already exists" };
	global_app = this;
}

ui::App::~App()
{
	global_app = nullptr;
}


auto ui::App::RegisterPage( std::string_view route_path, std::function<void( PageBuilder )>&& page_builder_fn ) -> void
{
	drogon::app().registerHandler(
		std::string{ route_path },
		[] (
			const drogon::HttpRequestPtr& request,
			std::function<void( const drogon::HttpResponsePtr& )>&& response_callback
		)
		{
			// This entrypoint will only provide the browser with a template html. The path will
			// handled later when the websockets connection has been established by the browser.
			auto html = ui::GetTemplateDocument( "./data/template.html" );

			auto response = drogon::HttpResponse::newHttpResponse();
			response->setContentTypeCode( drogon::CT_TEXT_HTML );
			response->setBody( std::move( html ) );

			response_callback( response );
		}
	);

	registered_page_list.push_back(
		Page {
			route_path,
			std::move( page_builder_fn )
		}
	);
}


auto ui::App::FindRegisteredPage( std::string_view route_path ) -> Page*
{
	auto it = std::ranges::find_if( registered_page_list, [route_path]( auto& p )
	{
		return p.route_path == route_path;
	} );
	if( it == registered_page_list.end() ) return nullptr;
	return &*it;
}


auto ui::App::Run() -> void
{
	drogon::app()
		.addListener("0.0.0.0", 8080)
		.run();
}


auto ui::GetGlobalApp() -> App&
{
	if( !global_app ) throw std::runtime_error{ "Global app instance not running" };
	return *global_app;
}
