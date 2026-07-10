module;

#include <string_view>
#include <functional>
#include <memory>

export module UI.PageBuilder;

import UI.PageBuilderCore;
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
export import UI.DOM.Modal;
export import UI.DOM.Card;
export import UI.DOM.Header;
export import UI.DOM.Footer;


namespace ui {


export
class PageBuilder
{
public:
	PageBuilder( PageBuilderCore& core, dom::Element* parent );
	PageBuilder( const PageBuilder& other ) = default;
	~PageBuilder() = default;

	auto operator=( const PageBuilder& other ) -> PageBuilder& = default;

	auto Scope( dom::Element* new_parent ) const -> PageBuilder;

	auto Label( std::string_view text ) -> dom::Label*;
	auto Button( std::string_view text, std::function<void()>&& on_click ) -> dom::Button*;
	auto Heading( std::string_view text, dom::HeadingStyle style = dom::HeadingStyle::H1 ) -> dom::Heading*;
	auto Paragraph( std::string_view text ) -> dom::Paragraph*;
	auto Span( std::string_view text ) -> dom::Span*;
	auto Link( std::string_view text, std::string_view link ) -> dom::Link*;
	auto Image( std::string_view link ) -> dom::Image*;
	auto HorizontalRule() -> dom::HorizontalRule*;

	template<typename ChildBuilderFn>
	auto Container( ChildBuilderFn&& child_builder_fn ) -> dom::Container*
	{
		auto* new_element = AddChild<ui::dom::Container>( "div", {} );
		BuildChildren( new_element, std::forward<ChildBuilderFn>( child_builder_fn ) );
		return new_element;
	}

	template<typename ChildBuilderFn>
	auto Card( ChildBuilderFn&& child_builder_fn ) -> dom::Card*
	{
		auto* new_element = AddChild<ui::dom::Card>( "article", {} );
		BuildChildren( new_element, std::forward<ChildBuilderFn>( child_builder_fn ) );
		return new_element;
	}

	template<typename ChildBuilderFn>
	auto Header( ChildBuilderFn&& child_builder_fn ) -> dom::Header*
	{
		auto* new_element = AddChild<ui::dom::Header>( "header", {} );
		BuildChildren( new_element, std::forward<ChildBuilderFn>( child_builder_fn ) );
		return new_element;
	}

	template<typename ChildBuilderFn>
	auto Footer( ChildBuilderFn&& child_builder_fn ) -> dom::Footer*
	{
		auto* new_element = AddChild<ui::dom::Footer>( "footer", {} );
		BuildChildren( new_element, std::forward<ChildBuilderFn>( child_builder_fn ) );
		return new_element;
	}

	template<typename ChildBuilderFn>
	auto Modal( ChildBuilderFn&& child_builder_fn ) -> dom::Modal*
	{
		auto* new_element = AddChild<ui::dom::Modal>( "dialog", {} );
		auto* client_updater = core->GetClientUpdater();

		new_element->open.OnSet(
			[client_updater, new_element]( const bool& in )
			{
				client_updater->SetModalOpen( new_element->id, in );
			}
		);

		BuildChildren( new_element, std::forward<ChildBuilderFn>( child_builder_fn ) );

		return new_element;
	}

private:
	template<
		typename T,
		typename ...ArgsT
	>
	auto AddChild(
		std::string_view tag,
		std::unordered_map<std::string, std::string> attributes,
		ArgsT&& ...args ) -> T*
	{
		auto new_element = std::make_unique<T>( std::forward<ArgsT>( args )... );
		auto new_element_ptr = new_element.get();

		auto* ce = GetParent();
		ce->children.push_back( std::move( new_element ) );
		new_element_ptr->id = std::string( "ui-" ) + ui::GenerateUUID();
		new_element_ptr->tag = tag;
		new_element_ptr->attributes = attributes;
		new_element_ptr->parent = ce;

		auto parent_id = std::string{ ce->id };
		if( parent_id.empty() ) parent_id = "root";

		core->GetClientUpdater()->CreateElement( parent_id, new_element_ptr->id, new_element_ptr->tag );

		return new_element_ptr;
	}

	template<typename ParentT, typename ChildBuilderFn>
	auto BuildChildren( ParentT* parent, ChildBuilderFn&& child_builder_fn ) -> void
	{
		BuildChildren( parent, parent, std::forward<ChildBuilderFn>( child_builder_fn ) );
	}

	template<typename ImmediateParentT, typename LogicalParentT, typename ChildBuilderFn>
	auto BuildChildren( ImmediateParentT* immediate_parent, LogicalParentT* logical_parent, ChildBuilderFn&& child_builder_fn ) -> void
	{
		if constexpr( std::is_invocable_v<ChildBuilderFn, PageBuilder, LogicalParentT*> )
		{
			std::invoke( std::forward<ChildBuilderFn>( child_builder_fn ), this->Scope( immediate_parent ), logical_parent );
		}
		else if constexpr( std::is_invocable_v<ChildBuilderFn, PageBuilder> )
		{
			std::invoke( std::forward<ChildBuilderFn>( child_builder_fn ), this->Scope( immediate_parent ) );
		}
		else
		{
			static_assert(
				std::is_invocable_v<ChildBuilderFn, PageBuilder> ||
				std::is_invocable_v<ChildBuilderFn, PageBuilder, LogicalParentT*>,
				"Child builder must be callable as fn() or fn(parent*)"
			);
		}
	}

	auto GetParent() -> dom::Element*;

	PageBuilderCore* core = nullptr;
	dom::Element* parent = nullptr;
};


}
