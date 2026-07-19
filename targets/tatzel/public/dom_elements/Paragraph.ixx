module;

#include <string_view>
#include <string>

export module UI.DOM.Paragraph;

export import UI.DOM.Element;

namespace tatzel::dom {

export
class Paragraph : public Element
{
public:
	using Element::Element;

	inline Paragraph( std::string_view id, Element* parent, std::string_view text ) :
		Element{ "p", id, parent }, text{ text }
	{}

	auto GetText() const noexcept -> std::string_view { return text; }
	auto SetText( std::string_view value ) -> void
	{
		if( text == value ) return;
		text = value;
		if( auto* queue = GetUpdateQueue() ) queue->SetText( id, text );
	}

private:
	std::string text;
};

}