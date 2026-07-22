module;

#include "PCH.hpp"

module UI.ElementAdapter.TatzelElementAdapter;


auto tatzel::TatzelElementAdapter::CreateElement( ui::LogicalElement* element ) -> ui::LogicalElement*
{
	return {};
}

/*
auto tatzel::TatzelElementAdapter::CreateLabel( ui::Label* element ) -> ui::LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelElementAdapter::CreateContainer( ui::Container* element ) -> ui::LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelElementAdapter::CreateButton( ui::Button* element ) -> ui::LogicalElement
{
	return { element, {} };
}

*/
auto tatzel::TatzelElementAdapter::CreateHeading( ui::Heading* element ) -> ui::Heading*
{
	return {};
}
/*

auto tatzel::TatzelElementAdapter::CreateParagraph( ui::Paragraph* element ) -> ui::LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelElementAdapter::CreateSpan( ui::Span* element ) -> ui::LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelElementAdapter::CreateLink( ui::Link* element ) -> ui::LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelElementAdapter::CreateImage( ui::Image* element ) -> ui::LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelElementAdapter::CreateHorizontalRule( ui::HorizontalRule* element ) -> ui::LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelElementAdapter::CreateModal( ui::Modal* element ) -> ui::LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelElementAdapter::CreateCard( ui::Card* element ) -> ui::LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelElementAdapter::CreateHeader( ui::Header* element ) -> ui::LogicalElement
{
	return { element, {} };
}


auto tatzel::TatzelElementAdapter::CreateFooter( ui::Footer* element ) -> ui::LogicalElement
{
	return { element, {} };
}
*/