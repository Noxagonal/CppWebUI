module;

#include "../PCH.hpp"

export module UI.DOM.Span;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


export
class Span : public Element
{
public:

	using Element::Element;

	inline Span(
		std::string_view id,
		Element* parent,
		std::string_view text
	) :
		Element{ "span", id, parent },
		text( std::string{ text } )
	{}

	Property<std::string> text;
};


}
