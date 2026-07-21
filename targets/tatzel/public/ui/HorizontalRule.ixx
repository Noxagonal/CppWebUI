module;

#include <string_view>

export module UI.DOM.HorizontalRule;

export import UI.UI.Element;

import UI.Property;


namespace tatzel::ui {


export
class HorizontalRule : public Element
{
public:

	using Element::Element;

	inline HorizontalRule(
		std::string_view id,
		Element* parent
	) :
		Element{ "hr", id, parent }
	{}
};


}
