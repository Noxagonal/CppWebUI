#include <string>

import UI;

auto main() -> int
{
	auto app = ui::App{};

	auto counter = 0;

	app.RegisterPage("/", [&]( ui::PageBuilder* ui ){
		auto* label1 = ui->Heading( "Test" );

		auto* modal = ui->Modal( [ui]( ui::dom::Modal* modal ){
			ui->Header( [ui]{
				ui->Paragraph( "This is header" );
			} );
			ui->Paragraph( "This is body" );
			ui->Footer( [ui, modal]{
				ui->Paragraph( "This is footer" );
				ui->Button( "Close", [modal]{
					if( modal ) modal->open = false;
				} );
			} );
		} );

		ui->Container( [ui]{
			ui->Label( "Test2" );
		} );
		ui->Container( [ui, label1, modal, &counter]{
			ui->Button( "Click me!", [label1, modal, &counter]{
				counter++;

				// label1.text is a custom property type with getters and
				// setters so setting it will update the browser immediately.
				label1->text = "Clicked times: " + std::to_string( counter );
				modal->open = true;
			} );
		} );
		ui->HorizontalRule();
	} );

	app.Run();

	return 0;
}
