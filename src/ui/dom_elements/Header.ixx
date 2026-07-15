module;

#include "../PCH.hpp"

export module UI.DOM.Header;

export import UI.DOM.Element;


namespace ui::dom {


export
class Header : public Element
{
public:

	using Element::Element;

	inline Header(
		std::string_view id,
		Element* parent
	) :
		Element{ "header", id, parent }
	{}
};


}
