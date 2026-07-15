module;

#include "../PCH.hpp"

export module UI.DOM.HorizontalRule;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


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
