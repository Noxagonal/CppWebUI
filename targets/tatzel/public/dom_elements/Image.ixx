module;

#include <string_view>
#include <string>

export module UI.DOM.Image;

export import UI.DOM.Element;

namespace tatzel::dom {

export
class Image : public Element
{
public:
	using Element::Element;

	inline Image( std::string_view id, Element* parent, std::string_view src ) :
		Element{ "img", id, parent }, src{ src }
	{}

	auto GetSource() const noexcept -> std::string_view { return src; }
	auto SetSource( std::string_view value ) -> void
	{
		if( src == value ) return;
		src = value;
		if( auto* queue = GetUpdateQueue() ) queue->SetAttribute( id, "src", src );
	}

private:
	std::string src;
};

}