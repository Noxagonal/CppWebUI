
#include <iostream>

import UI;


auto main() -> int
{
	auto app = ui::App{};

	auto counter = 0;

	app.RegisterPage("/", [&]( ui::PageBuilder& ui ){
		auto& label1 = ui.Label( "Test" );
 
		ui.Container( [&]{
			ui.Label( "Test2" );
		} );
		ui.Container( [&]{
			ui.Button( "Click me!", [&]{
				counter++;
				// label1.text is a custom property type with getters and
				// setters so setting it will update the browser immediately.
				label1.text = "Clicked times: " + std::to_string( counter );
			} );
		} );
	} );

	app.Run();

	return 0;
}
