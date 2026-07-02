module;

#include <string>

export module UI.DOM.Modal;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


export
class Modal : public Element
{
public:

	using Element::Element;

	Property<bool> open = false;
};


}
