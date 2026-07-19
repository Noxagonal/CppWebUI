export module UI.Renderer.Renderer;

export import UI.Renderer.LogicalElement;

export import UI.DOM.Element;
export import UI.DOM.Label;
export import UI.DOM.Container;
export import UI.DOM.Button;
export import UI.DOM.Heading;
export import UI.DOM.Paragraph;
export import UI.DOM.Span;
export import UI.DOM.Link;
export import UI.DOM.Image;
export import UI.DOM.HorizontalRule;
export import UI.DOM.Modal;
export import UI.DOM.Card;
export import UI.DOM.Header;
export import UI.DOM.Footer;


namespace tatzel {


export
class Renderer
{
public:

	virtual ~Renderer() = default;

	virtual auto CreateElement( dom::Element* element ) -> LogicalElement = 0;
	virtual auto CreateLabel( dom::Label* element ) -> LogicalElement = 0;
	virtual auto CreateContainer( dom::Container* element ) -> LogicalElement = 0;
	virtual auto CreateButton( dom::Button* element ) -> LogicalElement = 0;
	virtual auto CreateHeading( dom::Heading* element ) -> LogicalElement = 0;
	virtual auto CreateParagraph( dom::Paragraph* element ) -> LogicalElement = 0;
	virtual auto CreateSpan( dom::Span* element ) -> LogicalElement = 0;
	virtual auto CreateLink( dom::Link* element ) -> LogicalElement = 0;
	virtual auto CreateImage( dom::Image* element ) -> LogicalElement = 0;
	virtual auto CreateHorizontalRule( dom::HorizontalRule* element ) -> LogicalElement = 0;
	virtual auto CreateModal( dom::Modal* element ) -> LogicalElement = 0;
	virtual auto CreateCard( dom::Card* element ) -> LogicalElement = 0;
	virtual auto CreateHeader( dom::Header* element ) -> LogicalElement = 0;
	virtual auto CreateFooter( dom::Footer* element ) -> LogicalElement = 0;
};


}
