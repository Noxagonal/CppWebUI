module;

#include "../PCH.hpp"

export module UI.DOM.Changeable;


namespace tatzel::dom {


export
class Changeable
{
public:
	virtual ~Changeable() = default;

	virtual auto InvokeOnChange( std::string_view value ) -> void = 0;
};


}
