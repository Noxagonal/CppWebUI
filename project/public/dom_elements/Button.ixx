module;

#include <string_view>
#include <string>
#include <functional>

export module UI.DOM.Button;

export import UI.DOM.Element;
export import UI.DOM.Clickable;

import UI.Property;


namespace tatzel::dom {


export
class Button : public Element, public Clickable
{
public:

	using Element::Element;

	inline Button(
		std::string_view id,
		Element* parent,
		std::string_view text
	) :
		Element{ "button", id, parent },
		text{ std::string{ text } }
	{}

	inline virtual auto InvokeOnClick() -> void override
	{
		if( on_click ) on_click();
	}

	Property<std::string> text = std::string{ "Button" };
	std::function<void()> on_click;
};


}
