module;

#include <string_view>

export module UI.DOM.Container;

export import UI.UI.Element;


namespace tatzel::ui {


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
