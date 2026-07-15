module;

#include "../PCH.hpp"

export module UI.DOM.Modal;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


export
class Modal : public Element
{
public:

	using Element::Element;

	inline Modal(
		std::string_view id,
		Element* parent,
		bool open
	) :
		Element{ "dialog", id, parent },
		open{ open }
	{}

	Property<bool> open;
};


}
