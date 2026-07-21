#include <string>

import UI;

auto main() -> int
{
	auto app = tatzel::App{};

	auto counter = 0;

	app.RegisterPage("/", [&]( tatzel::PageBuilder<> ui ) {
		auto* label1 = ui.Heading( "Test" );
		label1->SetText( "test" );

		auto* modal = ui.Modal( []( auto ui, tatzel::dom::Modal* modal ) {
			ui.Card( [modal]( auto ui ){
				ui.Header( []( auto ui ){
					ui.Paragraph( "This is header" );
				} );
				ui.Paragraph( "This is body" );
				ui.Footer( [modal]( auto ui ) {
					ui.Paragraph( "This is footer" );
					ui.Button( "Close", [modal]{
						if( modal ) modal->SetOpen( false );
					} );
				} );
			} );
		} );

		ui.Container( []( auto ui ) {
			ui.Label( "Test2" );
		} );
		ui.Container( [label1, modal, &counter]( auto ui ) {
			ui.Button( "Click me!", [label1, modal, &counter]{
				counter++;

				// label1.text is a custom property type with getters and
				// setters so setting it will update the browser immediately.
				label1->SetText( "Clicked times: " + std::to_string( counter ) );
				if( modal ) modal->SetOpen( true );
			} );
		} );
		ui.HorizontalRule();
	} );

	app.Run();

	return 0;
}
