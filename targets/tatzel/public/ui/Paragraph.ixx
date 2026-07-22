module;

#include <string_view>
#include <string>

export module UI.DOM.Paragraph;

export import UI.UI.LogicalElement;

import UI.Property;


namespace tatzel::ui {

/*
export
class Paragraph : public LogicalElement
{
public:

	using LogicalElement::LogicalElement;

	inline Paragraph(
		std::string_view id,
		LogicalElement* parent,
		std::string_view text
	) :
		LogicalElement{ "p", id, parent },
		text{ std::string{ text } }
	{}

	Property<std::string> text;
};
*/

}
