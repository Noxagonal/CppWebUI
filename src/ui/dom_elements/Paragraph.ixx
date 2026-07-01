module;

#include <string>
#include <functional>

export module UI.DOM.Paragraph;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


export
class Paragraph : public Element
{
public:

	using Element::Element;

	ui::Property<std::string> text;
};


}
