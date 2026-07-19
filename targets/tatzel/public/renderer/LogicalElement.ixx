module;

#include <cassert>
#include <cstddef>
#include <span>
#include <string>
#include <string_view>

export module UI.Renderer.LogicalElement;

export import UI.Renderer.ElementPart;

import UI.DOM.Element;


namespace tatzel {


export
class LogicalElement
{
public:

	inline LogicalElement(
		dom::Element* element,
		std::span<const ElementPart> parts
	) :
		element{ element },
		parts{ parts }
	{
		assert( element );
	}

	LogicalElement( const LogicalElement& ) = default;
	LogicalElement( LogicalElement&& ) = default;
	~LogicalElement() = default;

	auto operator=( const LogicalElement& ) -> LogicalElement& = default;
	auto operator=( LogicalElement&& ) -> LogicalElement& = default;

	auto GetElement() const noexcept -> dom::Element*
	{
		return element;
	}

	auto GetParts() const noexcept -> std::span<const ElementPart>
	{
		return parts;
	}

	auto GetPartID( std::size_t part_index ) const -> std::string
	{
		assert( part_index < parts.size() );

		return std::string{ std::string_view{ element->id } }
			+ "--"
			+ std::string{ parts[ part_index ].name };
	}

private:

	dom::Element* element = nullptr;
	std::span<const ElementPart> parts;
};


}
