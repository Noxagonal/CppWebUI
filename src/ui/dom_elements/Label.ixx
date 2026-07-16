module;

#include "../PCH.hpp"

export module UI.DOM.Label;

export import UI.DOM.Element;

import UI.Property;


namespace tatzel::dom {


export
class Label : public Element
{
public:

	using Element::Element;

	inline Label(
		std::string_view id,
		Element* parent,
		std::string_view text
	) :
		Element{ "label", id, parent },
		text{ std::string{ text } }
	{}

	Property<std::string> text;
};


}
