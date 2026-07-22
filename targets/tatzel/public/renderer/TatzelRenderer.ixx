export module UI.Renderer.TatzelRenderer;

export import UI.Renderer.Renderer;


namespace tatzel {


export
class TatzelRenderer : public Renderer
{
public:

	TatzelRenderer() = default;
	TatzelRenderer( const TatzelRenderer& ) = default;
	TatzelRenderer( TatzelRenderer&& ) = default;
	~TatzelRenderer() override = default;

	auto operator=( const TatzelRenderer& ) -> TatzelRenderer& = default;
	auto operator=( TatzelRenderer&& ) -> TatzelRenderer& = default;

	auto CreateElement( ui::LogicalElement* element ) -> ui::LogicalElement* override;
	//auto CreateLabel( ui::Label* element ) -> ui::LogicalElement override;
	//auto CreateContainer( ui::Container* element ) -> ui::LogicalElement override;
	//auto CreateButton( ui::Button* element ) -> ui::LogicalElement override;
	auto CreateHeading( ui::Heading* element ) -> ui::Heading* override;
	//auto CreateParagraph( ui::Paragraph* element ) -> ui::LogicalElement override;
	//auto CreateSpan( ui::Span* element ) -> ui::LogicalElement override;
	//auto CreateLink( ui::Link* element ) -> ui::LogicalElement override;
	//auto CreateImage( ui::Image* element ) -> ui::LogicalElement override;
	//auto CreateHorizontalRule( ui::HorizontalRule* element ) -> ui::LogicalElement override;
	//auto CreateModal( ui::Modal* element ) -> ui::LogicalElement override;
	//auto CreateCard( ui::Card* element ) -> ui::LogicalElement override;
	//auto CreateHeader( ui::Header* element ) -> ui::LogicalElement override;
	//auto CreateFooter( ui::Footer* element ) -> ui::LogicalElement override;
};


}
