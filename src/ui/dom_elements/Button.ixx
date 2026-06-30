module;

#include <string>
#include <functional>

export module UI.DOM.Button;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


export
class Button : public Element
{
public:

	using Element::Element;

	ui::Property<std::string> text;
	std::function<void()> on_click;
};


}
