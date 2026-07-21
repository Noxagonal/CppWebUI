module;

#include <string_view>

export module UI.UI.Interface.Changeable;


namespace tatzel::dom {


export
class Changeable
{
public:
	virtual ~Changeable() = default;

	virtual auto InvokeOnChange( std::string_view value ) -> void = 0;
};


}
