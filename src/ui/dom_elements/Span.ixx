module;

#include <string>
#include <functional>

export module UI.DOM.Span;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


export
class Span : public Element
{
public:

	using Element::Element;

	Property<std::string> text = std::string{ "span" };
};


}
