module;

#include <string_view>
#include <string>

export module UI.DOM.Link;

export import UI.UI.LogicalElement;

import UI.Property;


namespace tatzel::ui {

/*
export
class Link : public LogicalElement
{
public:

	using LogicalElement::LogicalElement;

	inline Link(
		std::string_view id,
		LogicalElement* parent,
		std::string_view text,
		std::string_view href
	) :
		LogicalElement{ "a", id, parent },
		text{ std::string{ text } },
		href{ std::string{ href } }
	{}

	Property<std::string> text;
	Property<std::string> href;
};
*/

}
