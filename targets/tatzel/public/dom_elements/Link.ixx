module;

#include <string_view>
#include <string>

export module UI.DOM.Link;

export import UI.DOM.Element;

namespace tatzel::dom {

export
class Link : public Element
{
public:
	using Element::Element;

	inline Link( std::string_view id, Element* parent, std::string_view text, std::string_view href ) :
		Element{ "a", id, parent }, text{ text }, href{ href }
	{}

	auto GetText() const noexcept -> std::string_view { return text; }
	auto SetText( std::string_view value ) -> void
	{
		if( text == value ) return;
		text = value;
		if( auto* queue = GetUpdateQueue() ) queue->SetText( id, text );
	}

	auto GetHref() const noexcept -> std::string_view { return href; }
	auto SetHref( std::string_view value ) -> void
	{
		if( href == value ) return;
		href = value;
		if( auto* queue = GetUpdateQueue() ) queue->SetAttribute( id, "href", href );
	}

private:
	std::string text;
	std::string href;
};

}