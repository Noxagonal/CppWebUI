module;

#include <string_view>

export module UI.DOM.Footer;

export import UI.DOM.Element;


namespace ui::dom {


export
class Footer : public Element
{
public:

	using Element::Element;

	inline Footer(
		std::string_view id,
		Element* parent
	) :
		Element{ "footer", id, parent }
	{}
};


}
