module;

#include <string_view>
#include <string>
#include <functional>

export module UI.DOM.Button;

export import UI.DOM.Element;
export import UI.DOM.Clickable;


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
		text{ text }
	{}

	auto GetText() const noexcept -> std::string_view { return text; }

	auto SetText( std::string_view value ) -> void
	{
		if( text == value ) return;
		text = value;
		if( auto* queue = GetUpdateQueue() ) queue->SetText( id, text );
	}

	inline virtual auto InvokeOnClick() -> void override
	{
		if( on_click ) on_click();
	}

	std::function<void()> on_click;

private:
	std::string text{ "Button" };
};


}