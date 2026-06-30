module;

#include <string>

export module UI.DOM.Container;

export import UI.DOM.Element;


namespace ui::dom {


export
class Container : public Element
{
public:

	using Element::Element;
};


}
