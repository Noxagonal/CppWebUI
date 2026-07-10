module;

#include <string_view>
#include <functional>
#include <memory>

export module UI.PageBuilder;

import UI.PageBuilderCore;
import UI.ClientDOMTree;
import UI.ClientUpdater;
import UI.Utility;

export import UI.DOM.Element;
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
template<dom::ElementDerived ElementT = dom::Element>
class PageBuilder
{
public:
	PageBuilder(
		PageBuilderCore& core,
		ElementT* parent
	) :
		core( &core ),
		current_element( parent )
	{};
	PageBuilder( const PageBuilder& other ) = default;
	~PageBuilder() = default;

	auto operator=( const PageBuilder& other ) -> PageBuilder& = default;

	template<dom::ElementDerived NewParentScopeT = dom::Element>
	auto Scope( NewParentScopeT* new_parent ) const -> PageBuilder<NewParentScopeT>
	{
		return PageBuilder<NewParentScopeT> { *core, new_parent };
	}

	auto Label( std::string_view text ) -> dom::Label*
	{
		auto* new_element = AddChild<ui::dom::Label>( "label", {} );
		auto* client_updater = core->GetClientUpdater();

		new_element->text.OnSet(
			[client_updater, new_element]( const std::string& in )
			{
				client_updater->SetText( new_element->id, in );
			}
		);

		new_element->text = std::string{ text };

		return new_element;
	}

	auto Button( std::string_view text, std::function<void()>&& on_click ) -> dom::Button*
	{
		auto* new_element = AddChild<ui::dom::Button>( "button", {} );
		auto* client_updater = core->GetClientUpdater();

		new_element->text.OnSet(
			[client_updater, new_element]( const std::string& in )
			{
				client_updater->SetText( new_element->id, in );
			}
		);

		new_element->text = std::string{ text };
		new_element->on_click = std::move( on_click );

		client_updater->SetOnClick( new_element->id );

		return new_element;
	}

	auto Heading( std::string_view text, dom::HeadingStyle style = dom::HeadingStyle::H1 ) -> dom::Heading*
	{
		auto* new_element = AddChild<ui::dom::Heading>( HeadingStyleToTag( style ), {} );
		auto* client_updater = core->GetClientUpdater();

		new_element->text.OnSet(
			[client_updater, new_element]( const std::string& in )
			{
				client_updater->SetText( new_element->id, in );
			}
		);

		new_element->heading_style.OnSet(
			[client_updater, new_element]( const dom::HeadingStyle& in )
			{
				client_updater->SetTag( new_element->id, HeadingStyleToTag( in ) );
			}
		);

		new_element->text = std::string{ text };

		return new_element;
	}

	auto Paragraph( std::string_view text ) -> dom::Paragraph*
	{
		auto* new_element = AddChild<ui::dom::Paragraph>( "p", {} );
		auto* client_updater = core->GetClientUpdater();

		new_element->text.OnSet(
			[client_updater, new_element]( const std::string& in )
			{
				client_updater->SetText( new_element->id, in );
			}
		);

		new_element->text = std::string{ text };

		return new_element;
	}

	auto Span( std::string_view text ) -> dom::Span*
	{
		auto* new_element = AddChild<ui::dom::Span>( "span", {} );
		auto* client_updater = core->GetClientUpdater();

		new_element->text.OnSet(
			[client_updater, new_element]( const std::string& in )
			{
				client_updater->SetText( new_element->id, in );
			}
		);

		new_element->text = std::string{ text };

		return new_element;
	}


	auto Link( std::string_view text, std::string_view link ) -> dom::Link*
	{
		auto* new_element = AddChild<ui::dom::Link>( "a", {} );
		auto* client_updater = core->GetClientUpdater();

		new_element->text.OnSet(
			[client_updater, new_element]( const std::string& in )
			{
				client_updater->SetText( new_element->id, in );
			}
		);

		new_element->href.OnSet(
			[client_updater, new_element]( const std::string& in )
			{
				client_updater->SetAttribute( new_element->id, "href", in );
			}
		);

		new_element->text = std::string{ text };
		new_element->href = std::string{ link };

		return new_element;
	}


	auto Image( std::string_view link ) -> dom::Image*
	{
		auto* new_element = AddChild<ui::dom::Image>( "img", {} );
		auto* client_updater = core->GetClientUpdater();

		new_element->src.OnSet(
			[client_updater, new_element]( const std::string& in )
			{
				client_updater->SetAttribute( new_element->id, "src", in );
			}
		);

		new_element->src = std::string{ link };

		return new_element;
	}


	auto HorizontalRule() -> dom::HorizontalRule*
	{
		auto* new_element = AddChild<ui::dom::HorizontalRule>( "hr", {} );

		return new_element;
	}


	auto GetParent() -> dom::Element*
	{
		if( current_element == nullptr ) throw std::runtime_error{ "Missing current element" };
		return current_element;
	}

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
		if constexpr( std::is_invocable_v<ChildBuilderFn, PageBuilder, ParentT*> )
		{
			std::invoke( std::forward<ChildBuilderFn>( child_builder_fn ), this->Scope( parent ), parent );
		}
		else if constexpr( std::is_invocable_v<ChildBuilderFn, PageBuilder> )
		{
			std::invoke( std::forward<ChildBuilderFn>( child_builder_fn ), this->Scope( parent ) );
		}
		else
		{
			static_assert(
				std::is_invocable_v<ChildBuilderFn, PageBuilder> ||
				std::is_invocable_v<ChildBuilderFn, PageBuilder, ParentT*>,
				"Child builder must be callable as fn(PageBuilder) or fn(PageBuilder, parent*)"
			);
		}
	}

	auto GetCurrent() -> ElementT* { return current_element; }

private:

	PageBuilderCore* core = nullptr;
	ElementT* current_element = nullptr;
};


template<dom::ElementDerived ElementT>
PageBuilder( ElementT& ) -> PageBuilder<ElementT>;


}
