module;

#include "../PCH.hpp"

export module UI.DOM.Paragraph;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


export
class Paragraph : public Element
{
public:

	using Element::Element;

	inline Paragraph(
		std::string_view id,
		Element* parent,
		std::string_view text
	) :
		Element{ "p", id, parent },
		text{ std::string{ text } }
	{}

	ui::Property<std::string> text;
};


}
