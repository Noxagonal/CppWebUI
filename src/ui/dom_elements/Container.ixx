module;

#include "../PCH.hpp"

export module UI.DOM.Container;

export import UI.DOM.Element;


namespace ui::dom {


export
class Container : public Element
{
public:

	using Element::Element;

	inline Container(
		std::string_view id,
		Element* parent
	) :
		Element{ "div", id, parent }
	{}
};


}
