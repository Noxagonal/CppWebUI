module;

#include "PCH.hpp"

module UI.Renderer.TatzelRenderer;


auto tatzel::TatzelRenderer::CreateElement( dom::Element* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateLabel( dom::Label* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateContainer( dom::Container* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateButton( dom::Button* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateHeading( dom::Heading* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateParagraph( dom::Paragraph* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateSpan( dom::Span* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateLink( dom::Link* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateImage( dom::Image* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateHorizontalRule( dom::HorizontalRule* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateModal( dom::Modal* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateCard( dom::Card* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateHeader( dom::Header* element ) -> LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelRenderer::CreateFooter( dom::Footer* element ) -> LogicalElement
{
	return { element, {} };
}
