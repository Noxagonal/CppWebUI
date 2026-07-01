module;

#include <string>
#include <string_view>
#include <functional>
#include <stdexcept>

export module UI.DOM.Heading;

export import UI.DOM.Element;

import UI.Property;


namespace ui::dom {


export
enum class HeadingStyle
{
	H1,
	H2,
	H3,
	H4,
	H5,
	H6,
};


export
inline auto HeadingStyleToTag( HeadingStyle style ) -> std::string_view
{
	switch( style )
	{
	case HeadingStyle::H1:
		return "h1";
	case HeadingStyle::H2:
		return "h2";
	case HeadingStyle::H3:
		return "h3";
	case HeadingStyle::H4:
		return "h4";
	case HeadingStyle::H5:
		return "h5";
	case HeadingStyle::H6:
		return "h6";
	}

	throw std::runtime_error{ "Invalid heading style" };
}


export
class Heading : public Element
{
public:

	using Element::Element;

	ui::Property<std::string> text;
	ui::Property<HeadingStyle> heading_style = HeadingStyle::H1;
};


}
