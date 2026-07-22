module;

#include <string_view>
#include <string>

export module UI.DOM.Label;

export import UI.UI.LogicalElement;

import UI.Property;


namespace tatzel::ui {

/*
export
class Label : public LogicalElement
{
public:

	using LogicalElement::LogicalElement;

	inline Label(
		std::string_view id,
		LogicalElement* parent,
		std::string_view text
	) :
		LogicalElement{ "label", id, parent },
		text{ std::string{ text } }
	{}

	Property<std::string> text;
};
*/

}
