module;

#include <string_view>

export module UI.DOM.Modal;

export import UI.DOM.Element;

namespace tatzel::dom {

export
class Modal : public Element
{
public:
	using Element::Element;

	inline Modal( std::string_view id, Element* parent, bool open ) :
		Element{ "dialog", id, parent }, open{ open }
	{}

	auto IsOpen() const noexcept -> bool { return open; }
	auto SetOpen( bool value ) -> void
	{
		if( open == value ) return;
		open = value;
		if( auto* queue = GetUpdateQueue() ) queue->SetModalOpen( id, open );
	}

private:
	bool open = false;
};

}