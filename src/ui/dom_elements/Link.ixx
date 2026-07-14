module;

#include <string>
#include <string_view>

export module UI.DOM.Link;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


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

	ui::Property<std::string> text;
	ui::Property<std::string> href;
};


}
