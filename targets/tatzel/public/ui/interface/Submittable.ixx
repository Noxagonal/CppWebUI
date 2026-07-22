module;

export module UI.UI.Interface.Submittable;


namespace tatzel::ui::interface {


export
class Submittable
{
public:
	virtual ~Submittable() = default;

	virtual auto InvokeOnSubmit() -> void = 0;
};


}
