module;

export module UI.UI.Interface.Clickable;


namespace tatzel::dom {


export
class Clickable
{
public:
	virtual ~Clickable() = default;

	virtual auto InvokeOnClick() -> void = 0;
};


}
