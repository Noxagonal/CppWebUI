module;

#include <cstddef>
#include <optional>
#include <span>
#include <string_view>
#include <utility>

export module UI.Renderer.ElementPart;


namespace tatzel {


export
class ElementPart
{
public:

	using Attribute = std::pair<std::string_view, std::string_view>;

	inline ElementPart(
		std::string_view name,
		std::string_view tag,
		std::span<const std::string_view> classes = {},
		std::span<const Attribute> attributes = {},
		std::optional<std::size_t> parent_index = std::nullopt
	) :
		name{ name },
		tag{ tag },
		classes{ classes },
		attributes{ attributes },
		parent_index{ parent_index }
	{}

	std::string_view name;
	std::string_view tag;
	std::span<const std::string_view> classes;
	std::span<const Attribute> attributes;
	std::optional<std::size_t> parent_index;
};


}
