#include <drogon/drogon.h>

#include "drogon/HttpAppFramework.h"
#include "ui/WsController.hpp"

import UI.PageBuilder;


auto main() -> int
{
	drogon::app().loadConfigFile( "./data/drogon_config.json" );

	drogon::app()
		.addListener("0.0.0.0", 8080)
		.run();

	return 0;
}
