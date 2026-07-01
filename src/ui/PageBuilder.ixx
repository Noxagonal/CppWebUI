module;

#include <string_view>
#include <functional>
#include <memory>

export module UI.PageBuilder;

import UI.ClientDOMTree;
import UI.ClientUpdater;
import UI.Utility;

export import UI.DOM.Label;
export import UI.DOM.Container;
export import UI.DOM.Button;
export import UI.DOM.Heading;
export import UI.DOM.Paragraph;
export import UI.DOM.Span;
export import UI.DOM.Link;
export import UI.DOM.Image;
export import UI.DOM.HorizontalRule;


namespace ui {


export
class PageBuilder
{
public:
	PageBuilder( ClientDOMTree& dom_tree, ClientUpdater& client_updater );
	PageBuilder( const PageBuilder& ) = delete;
	PageBuilder( PageBuilder&& ) = default;
	~PageBuilder() = default;

	auto operator=( const PageBuilder& ) -> PageBuilder& = delete;
	auto operator=( PageBuilder&& ) -> PageBuilder& = default;

	auto Label( std::string_view text ) -> dom::Label&;
	auto Container( std::function<void()>&& child_builder ) -> dom::Container&;
	auto Button( std::string_view text, std::function<void()>&& on_click ) -> dom::Button&;
	auto Heading( std::string_view text, dom::HeadingStyle style = dom::HeadingStyle::H1 ) -> dom::Heading&;
	auto Paragraph( std::string_view text ) -> dom::Paragraph&;
	auto Span( std::string_view text ) -> dom::Span&;
	auto Link( std::string_view text, std::string_view link ) -> dom::Link&;
	auto Image( std::string_view link ) -> dom::Image&;
	auto HorizontalRule() -> dom::HorizontalRule&;

private:
	template<
		typename T,
		typename ...ArgsT
	>
	auto AddChild(
		std::string_view tag,
		std::unordered_map<std::string, std::string> attributes,
		ArgsT&& ...args ) -> T&
	{
		auto new_element = std::make_unique<T>( std::forward<ArgsT>( args )... );
		auto new_element_ptr = new_element.get();

		auto& ce = GetCurrentElement();
		ce.children.push_back( std::move( new_element ) );
		new_element_ptr->id = std::string( "ui-" ) + ui::GenerateUUID();
		new_element_ptr->tag = tag;
		new_element_ptr->attributes = attributes;
		new_element_ptr->parent = &ce;

		auto parent_id = std::string{ ce.id };
		if( parent_id.empty() ) parent_id = "root";

		client_updater->CreateElement( parent_id, new_element_ptr->id, new_element_ptr->tag );

		return *new_element_ptr;
	}

	auto GetCurrentElement() -> dom::Element&;

	auto GoToChild( const dom::Element& child ) -> dom::Element&;
	auto GoToParent() -> dom::Element&;

	ClientDOMTree* dom_tree;
	dom::Element* current_element = nullptr;
	ClientUpdater* client_updater = nullptr;
};


}
