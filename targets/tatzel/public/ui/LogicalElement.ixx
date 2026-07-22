module;

#include <cassert>
#include <cstddef>
#include <span>
#include <string>
#include <string_view>
#include <vector>
#include <memory>

export module UI.UI.LogicalElement;

export import UI.DOM.ElementPart;


namespace tatzel::ui {


export
class LogicalElement
{
public:

	inline LogicalElement(
		std::string_view id,
		LogicalElement* parent,
		std::span<const dom::ElementPart> parts
	) :
		id{ id },
		parent{ parent },
		part_list{ parts.begin(), parts.end() }
	{}

	LogicalElement( const LogicalElement& ) = default;
	LogicalElement( LogicalElement&& ) = default;
	virtual ~LogicalElement() = default;

	auto operator=( const LogicalElement& ) -> LogicalElement& = default;
	auto operator=( LogicalElement&& ) -> LogicalElement& = default;

	auto GetID() const noexcept -> std::string_view { return id; }
	auto GetParent() const noexcept -> LogicalElement* { return parent; }
	auto GetParts() const noexcept -> std::span<const dom::ElementPart> { return part_list; }

	auto GetPartID( std::size_t part_index ) const -> std::string
	{
		assert( part_index < part_list.size() );

		return std::string{ std::string_view{ GetID() } }
			+ "--"
			+ std::string{ part_list[ part_index ].name };
	}

	template<typename ElementT>
	requires( std::derived_from<ElementT, LogicalElement> )
	auto InsertChild( std::unique_ptr<ElementT> child ) -> ElementT*
	{
		auto child_ptr = child.get();
		child_list.push_back( std::move( child ) );
		return child_ptr;
	}

	auto GetChildren() const -> const std::vector<std::unique_ptr<LogicalElement>>& { return child_list; }

private:

	std::string id;
	LogicalElement* parent = nullptr;
	std::vector<dom::ElementPart> part_list;
	std::vector<std::unique_ptr<LogicalElement>> child_list;
};


export
template<typename T>
concept LogicalElementDerived = std::derived_from<T, LogicalElement>;


}
