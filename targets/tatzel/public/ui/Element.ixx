module;

#include <string_view>
#include <string>
#include <memory>

export module UI.UI.Element;

import UI.Property;

/*
namespace tatzel {

class ClientDOMTree;
class PageBuilder;

}
*/


namespace tatzel::ui {


export
class Element
{

	// TODO: C++ modules currently prevent this.
	//friend class ::tatzel::ClientDOMTree;
	//friend class ::tatzel::PageBuilder;

public:

	inline Element(
		std::string_view tag,
		std::string_view id,
		Element* parent
	) :
		tag{ std::string{ tag } },
		id{ std::string{ id } },
		parent{ parent }
	{}

	Element( const Element& ) = delete;
	Element( Element&& ) = default;
	virtual ~Element() = default;

	auto operator=( const Element& ) -> Element& = delete;
	auto operator=( Element&& ) -> Element& = default;

	auto GetChildren() -> const std::vector<std::unique_ptr<Element>>&
	{
		return children;
	}

	template<typename ChildT>
	auto InsertChild( std::unique_ptr<ChildT>&& child ) -> void
	{
		static_assert( std::is_base_of_v<Element, ChildT>, "Child must be inherited from Element" );
		children.push_back( std::move( child ) );
	}

	auto ClearChildren() -> void
	{
		children.clear();
	}

	auto GetAttributes() -> const std::unordered_map<std::string, std::string>&
	{
		return attributes;
	}

	ReadOnlyProperty<std::string> tag;
	ReadOnlyProperty<std::string> id;
	ReadOnlyProperty<Element*> parent;

private:

	std::unordered_map<std::string, std::string> attributes;
	std::vector<std::unique_ptr<Element>> children;
};


export
template<typename T>
concept ElementDerived = std::derived_from<T, Element>;


}
