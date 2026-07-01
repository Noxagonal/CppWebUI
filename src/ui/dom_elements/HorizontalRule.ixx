module;

#include <string>
#include <functional>

export module UI.DOM.HorizontalRule;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


export
class HorizontalRule : public Element
{
public:

	using Element::Element;
};


}
