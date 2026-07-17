module;

#include "../PCH.hpp"

export module UI.DOM.Link;

export import UI.DOM.Element;

import UI.Property;


namespace tatzel::dom {


export
class Link : public Element
{
public:

	using Element::Element;

	inline Link(
		std::string_view id,
		Element* parent,
		std::string_view text,
		std::string_view href
	) :
		Element{ "a", id, parent },
		text{ std::string{ text } },
		href{ std::string{ href } }
	{}

	Property<std::string> text;
	Property<std::string> href;
};


}
