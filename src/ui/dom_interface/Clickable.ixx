module;

#include "../PCH.hpp"

export module UI.DOM.Clickable;


namespace ui::dom {


export
class Clickable
{
public:
	virtual ~Clickable() = default;

	virtual auto InvokeOnClick() -> void = 0;
};


}
