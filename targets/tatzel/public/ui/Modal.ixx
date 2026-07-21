module;

#include <string_view>

export module UI.DOM.Modal;

export import UI.UI.Element;

import UI.Property;


namespace tatzel::ui {


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
