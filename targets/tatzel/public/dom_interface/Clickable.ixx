module;

export module UI.DOM.Clickable;


namespace tatzel::dom {


export
class Clickable
{
public:
	virtual ~Clickable() = default;

	virtual auto InvokeOnClick() -> void = 0;
};


}
