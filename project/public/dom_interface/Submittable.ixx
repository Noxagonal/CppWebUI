module;

export module UI.DOM.Submittable;


namespace tatzel::dom {


export
class Submittable
{
public:
	virtual ~Submittable() = default;

	virtual auto InvokeOnSubmit() -> void = 0;
};


}
