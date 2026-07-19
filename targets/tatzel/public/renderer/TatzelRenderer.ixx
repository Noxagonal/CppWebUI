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

	auto CreateElement( dom::Element* element ) -> LogicalElement override;
	auto CreateLabel( dom::Label* element ) -> LogicalElement override;
	auto CreateContainer( dom::Container* element ) -> LogicalElement override;
	auto CreateButton( dom::Button* element ) -> LogicalElement override;
	auto CreateHeading( dom::Heading* element ) -> LogicalElement override;
	auto CreateParagraph( dom::Paragraph* element ) -> LogicalElement override;
	auto CreateSpan( dom::Span* element ) -> LogicalElement override;
	auto CreateLink( dom::Link* element ) -> LogicalElement override;
	auto CreateImage( dom::Image* element ) -> LogicalElement override;
	auto CreateHorizontalRule( dom::HorizontalRule* element ) -> LogicalElement override;
	auto CreateModal( dom::Modal* element ) -> LogicalElement override;
	auto CreateCard( dom::Card* element ) -> LogicalElement override;
	auto CreateHeader( dom::Header* element ) -> LogicalElement override;
	auto CreateFooter( dom::Footer* element ) -> LogicalElement override;
};


}
