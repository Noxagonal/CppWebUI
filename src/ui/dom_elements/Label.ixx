module;

#include <string>
#include <string_view>

export module UI.DOM.Label;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


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

	ui::Property<std::string> text;
};


}
