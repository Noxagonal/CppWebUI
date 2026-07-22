module;

#include <memory>
#include <vector>
#include <functional>
#include <cassert>

export module UI.PageBuilder;

import UI.PageBuilderCore;
import UI.ClientUpdater;
import UI.Utility;

export import UI.UI.LogicalElement;
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


namespace tatzel {


export
template<ui::LogicalElementDerived ElementT = ui::LogicalElement>
class PageBuilder
{
public:
	PageBuilder(
		PageBuilderCore& core,
		ElementT& parent
	) :
		core( &core ),
		parent( &parent )
	{}
	PageBuilder( const PageBuilder& other ) = default;
	~PageBuilder() = default;

	auto operator=( const PageBuilder& other ) -> PageBuilder& = default;

	template<ui::LogicalElementDerived NewParentScopeT = ui::LogicalElement>
	auto Scope( NewParentScopeT& new_parent ) const -> PageBuilder<NewParentScopeT>
	{
		return { *core, new_parent };
	}

	auto Heading( std::string_view text, ui::HeadingStyle style = ui::HeadingStyle::H1 ) -> ui::Heading*
	{
		auto* new_element = AddChild<tatzel::ui::Heading>();

		return new_element;
	}

	/*
	auto Label( std::string_view text ) -> dom::Label*
	{
		auto* new_element = AddChild<tatzel::ui::Label>( text );

		this->BindSetText( new_element, &new_element->text );

		new_element->text = text;

		return new_element;
	}

	auto Button( std::string_view text, std::function<void()> on_click ) -> dom::Button*
	{
		auto* new_element = AddChild<tatzel::ui::Button>( text );

		this->BindSetText( new_element, &new_element->text );
		this->BindEventOnClick( new_element );

		new_element->text = text;
		new_element->on_click = std::move( on_click );

		return new_element;
	}

	auto Paragraph( std::string_view text ) -> dom::Paragraph*
	{
		auto* new_element = AddChild<tatzel::ui::Paragraph>( text );

		this->BindSetText( new_element, &new_element->text );

		new_element->text = text;

		return new_element;
	}

	auto Span( std::string_view text ) -> dom::Span*
	{
		auto* new_element = AddChild<tatzel::ui::Span>( text );

		this->BindSetText( new_element, &new_element->text );

		new_element->text = text;

		return new_element;
	}

	auto Link( std::string_view text, std::string_view href ) -> dom::Link*
	{
		auto* new_element = AddChild<tatzel::ui::Link>( text, href );

		this->BindSetText( new_element, &new_element->text );
		this->BindSetAttribute( new_element, &new_element->href, "href" );

		new_element->text = text;
		new_element->href = href;

		return new_element;
	}

	auto Image( std::string_view src ) -> dom::Image*
	{
		auto* new_element = AddChild<tatzel::ui::Image>( src );

		this->BindSetAttribute( new_element, &new_element->src, "src" );

		new_element->src = src;

		return new_element;
	}

	auto HorizontalRule() -> dom::HorizontalRule*
	{
		auto* new_element = AddChild<tatzel::ui::HorizontalRule>();

		return new_element;
	}

	template<typename ChildBuilderFn>
	auto Container( ChildBuilderFn&& child_builder_fn ) -> dom::Container*
	{
		auto* new_element = AddChild<tatzel::ui::Container>();

		this->BuildChildren( *new_element, std::forward<ChildBuilderFn>( child_builder_fn ) );

		return new_element;
	}

	template<typename ChildBuilderFn>
	auto Card( ChildBuilderFn&& child_builder_fn ) -> dom::Card*
	{
		auto* new_element = AddChild<tatzel::ui::Card>();

		this->BuildChildren( *new_element, std::forward<ChildBuilderFn>( child_builder_fn ) );

		return new_element;
	}

	template<typename ChildBuilderFn>
	auto Header( ChildBuilderFn&& child_builder_fn ) -> dom::Header*
	{
		auto* new_element = AddChild<tatzel::ui::Header>();

		this->BuildChildren( *new_element, std::forward<ChildBuilderFn>( child_builder_fn ) );

		return new_element;
	}

	template<typename ChildBuilderFn>
	auto Footer( ChildBuilderFn&& child_builder_fn ) -> dom::Footer*
	{
		auto* new_element = AddChild<tatzel::ui::Footer>();

		this->BuildChildren( *new_element, std::forward<ChildBuilderFn>( child_builder_fn ) );

		return new_element;
	}
*/
//	template<typename ChildBuilderFn>
//	auto Modal( ChildBuilderFn&& child_builder_fn ) -> dom::Modal*
//	{
//		auto* new_element = AddChild<tatzel::ui::Modal>( false /* Closed by default */ );
//
//		this->BindSetModalOpen( new_element, &new_element->open );
//
//		this->BuildChildren( *new_element, std::forward<ChildBuilderFn>( child_builder_fn ) );
//
//		return new_element;
//	}

private:

	auto BindSetProperty(
		ui::LogicalElementDerived auto* element,
		auto* property,
		auto&& update_fn
	) -> void
	{
		assert( element );
		assert( property );

		using UpdateFn = decltype( update_fn );

		auto* client_updater = this->core->GetClientUpdater();
		assert( client_updater );
		auto element_id = std::string_view{ element->GetID() };

		property->OnSet( [client_updater, element_id = std::string{ element_id }, update_fn = std::forward<UpdateFn>( update_fn ) ]( const auto& value ) mutable {
			std::invoke( update_fn, client_updater, element_id, value );
		} );
	}

	auto BindSetText(
		ui::LogicalElementDerived auto* element,
		auto* property
	) -> void
	{
		BindSetProperty(
			element,
			property,
			[]( ClientUpdater* updater, std::string_view id, std::string_view value ) {
				updater->SetText( id, value );
			}
		);
	}

	auto BindSetAttribute(
		ui::LogicalElementDerived auto* element,
		auto* property,
		std::string_view attribute
	) -> void
	{
		BindSetProperty(
			element,
			property,
			[attribute = std::string{ attribute }]( ClientUpdater* updater, std::string_view id, std::string_view value ) {
				updater->SetAttribute( id, attribute, value );
			}
		);
	}

	auto BindSetModalOpen(
		ui::LogicalElementDerived auto* element,
		auto* property
	) -> void
	{
		BindSetProperty(
			element,
			property,
			[]( ClientUpdater* updater, std::string_view id, bool value ) {
				updater->SetModalOpen( id, value );
			}
		);
	}

	auto BindEventOnClick( ui::LogicalElementDerived auto* element ) -> void
	{
		assert( element );
		auto* client_updater = this->core->GetClientUpdater();
		assert( client_updater );
		client_updater->SetOnClick( element->id );
	}

	template<ui::LogicalElementDerived NewElementT>
	auto AddChild() -> NewElementT*
	{
		auto* owning_parent = this->parent;
		assert( owning_parent );

		// TODO: ElementAdapter should be invoked here to set up the element parts.
		auto parts = std::vector<dom::ElementPart>{
			{ "root", "div" }
		};

		auto new_element = std::make_unique<NewElementT>(
			this->GenerateElementUUID(),
			owning_parent,
			parts
		);
		auto* new_element_ptr = new_element.get();

		// TODO: Serialize and add initial values when creating a new element
		// so we don't need to separately assign the properties after creation.

		owning_parent->InsertChild( std::move( new_element ) );

		auto* client_updater = this->core->GetClientUpdater();
		assert( client_updater );
		// TODO: This needs to be changed to reflect the new architecture with element parts / dom parts.
		client_updater->CreateElement(
			owning_parent->GetID(),
			new_element_ptr->GetID(),
			new_element_ptr->GetParts()[ 0 ].tag
		);

		return new_element_ptr;
	}

	template<ui::LogicalElementDerived ParentT, typename ChildBuilderFn>
	auto BuildChildren( ParentT& parent, ChildBuilderFn&& child_builder_fn ) -> void
	{
		using ScopedBuilderT = PageBuilder<ParentT>;
		auto scoped_builder = this->Scope( parent );

		if constexpr( std::is_invocable_v<ChildBuilderFn&&, ScopedBuilderT&, ParentT*> )
		{
			std::invoke( std::forward<ChildBuilderFn>( child_builder_fn ), scoped_builder, &parent );
		}
		else if constexpr( std::is_invocable_v<ChildBuilderFn&&, ScopedBuilderT&> )
		{
			std::invoke( std::forward<ChildBuilderFn>( child_builder_fn ), scoped_builder );
		}
		else
		{
			static_assert(
				std::is_invocable_v<ChildBuilderFn&&, ScopedBuilderT&> ||
				std::is_invocable_v<ChildBuilderFn&&, ScopedBuilderT&, ParentT*>,
				"Child builder must be callable as fn(PageBuilder<ParentT>) or fn(PageBuilder<ParentT>, ParentT*)"
			);
		}
	}

	auto GetParent() const noexcept -> ElementT* { return parent; }
	auto GetRoot() const noexcept -> ui::LogicalElement* { return core->GetRootElement(); }

private:

	auto GenerateElementUUID() const -> std::string
	{
		return std::string( "ui-" ) + tatzel::GenerateUUID();
	}

	PageBuilderCore* core = nullptr;
	ElementT* parent = nullptr;
};


}
