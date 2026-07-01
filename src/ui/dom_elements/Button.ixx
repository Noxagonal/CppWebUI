module;

#include <string>
#include <functional>

export module UI.DOM.Button;

export import UI.DOM.Element;
export import UI.DOM.Clickable;

import UI.Property;


namespace ui::dom {


export
class Button : public Element, public Clickable
{
public:

	using Element::Element;

	inline virtual auto InvokeOnClick() -> void override
	{
		if( on_click ) on_click();
	}

	ui::Property<std::string> text = std::string{ "Button" };
	std::function<void()> on_click;
};


}
