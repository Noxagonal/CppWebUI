module;

#include <string_view>
#include <string>

export module UI.DOM.Image;

export import UI.UI.LogicalElement;

import UI.Property;


namespace tatzel::ui {

/*
export
class Image : public LogicalElement
{
public:

	using LogicalElement::LogicalElement;

	inline Image(
		std::string_view id,
		LogicalElement* parent,
		std::string_view src
	) :
		LogicalElement{ "img", id, parent },
		src{ std::string{ src } }
	{}

	Property<std::string> src;
};
*/

}
