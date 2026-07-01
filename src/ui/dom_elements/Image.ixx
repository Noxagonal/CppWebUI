module;

#include <string>
#include <functional>

export module UI.DOM.Image;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


export
class Image : public Element
{
public:

	using Element::Element;

	ui::Property<std::string> src;
};


}
