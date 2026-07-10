module;

#include <concepts>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

export module UI.DOM.Element;


namespace ui::dom {


export
class Element
{
public:

	Element() = default;
	Element( const Element& ) = delete;
	Element( Element&& ) = default;
	virtual ~Element() = default;

	auto operator=( const Element& ) -> Element& = delete;
	auto operator=( Element&& ) -> Element& = default;

	std::string id;
	std::string tag;
	std::unordered_map<std::string, std::string> attributes;
	std::vector<std::unique_ptr<Element>> children;
	Element* parent = nullptr;
};


export
template<typename T>
concept ElementDerived = std::derived_from<T, Element>;


}
