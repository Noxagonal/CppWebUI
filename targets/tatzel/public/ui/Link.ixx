module;

#include <string_view>
#include <string>

export module UI.DOM.Link;

export import UI.UI.Element;

import UI.Property;


namespace tatzel::ui {


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
