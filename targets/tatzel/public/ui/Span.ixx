module;

#include <string_view>
#include <string>

export module UI.DOM.Span;

export import UI.UI.LogicalElement;

import UI.Property;


namespace tatzel::ui {

/*
export
class Span : public LogicalElement
{
public:

	using LogicalElement::LogicalElement;

	inline Span(
		std::string_view id,
		LogicalElement* parent,
		std::string_view text
	) :
		LogicalElement{ "span", id, parent },
		text( std::string{ text } )
	{}

	Property<std::string> text;
};
*/

}
