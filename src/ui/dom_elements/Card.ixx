module;

#include "../PCH.hpp"

export module UI.DOM.Card;

export import UI.DOM.Element;


namespace tatzel::dom {


export
class Card : public Element
{
public:

	using Element::Element;

	inline Card(
		std::string_view id,
		Element* parent
	) :
		Element{ "article", id, parent }
	{}
};


}
