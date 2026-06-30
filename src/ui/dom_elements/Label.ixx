module;

#include <string>

export module UI.DOM.Label;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


export
class Label : public Element
{
public:

	using Element::Element;

	ui::Property<std::string> text;
};


}
