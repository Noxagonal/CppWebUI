#include <string>

import UI;

auto main() -> int
{
	auto app = tatzel::App{};

	auto counter = 0;

	app.RegisterPage("/", [&]( tatzel::PageBuilder<> ui ) {
		auto* heading = ui.Heading( "Test" );
	} );

	app.Run();

	return 0;
}
