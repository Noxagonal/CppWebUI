module;

#include "../PCH.hpp"

export module UI.DOM.Image;

export import UI.DOM.Element;

import UI.Property;


namespace tatzel::dom {


export
class Image : public Element
{
public:

	using Element::Element;

	inline Image(
		std::string_view id,
		Element* parent,
		std::string_view src
	) :
		Element{ "img", id, parent },
		src{ std::string{ src } }
	{}

	Property<std::string> src;
};


}
