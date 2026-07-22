module;

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <span>
#include <utility>

export module UI.DOM.ElementPart;


namespace tatzel::dom {


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
		name{ std::string{ name } },
		tag{ std::string{ tag } },
		classes{ classes.begin(), classes.end() },
		attributes{ attributes.begin(), attributes.end() },
		parent_index{ parent_index }
	{}

	std::string name;
	std::string tag;
	std::vector<std::string> classes;
	std::vector<Attribute> attributes;
	std::optional<std::size_t> parent_index;
};


}
