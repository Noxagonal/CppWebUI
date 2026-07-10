module;

#include <string_view>
#include <functional>
#include <stdexcept>

module UI.PageBuilder;

import UI.PageBuilderCore;


ui::PageBuilder::PageBuilder( PageBuilderCore& core, dom::Element* parent ) :
	core( &core ),
	parent( parent )
{}


auto ui::PageBuilder::Scope( dom::Element* new_parent ) const -> ui::PageBuilder
{
	return PageBuilder { *core, new_parent };
}


auto ui::PageBuilder::Label( std::string_view text ) -> ui::dom::Label*
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


auto ui::PageBuilder::Button( std::string_view text, std::function<void()>&& on_click ) -> dom::Button*
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


auto ui::PageBuilder::Heading( std::string_view text, dom::HeadingStyle style ) -> dom::Heading*
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


auto ui::PageBuilder::Paragraph( std::string_view text ) -> dom::Paragraph*
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


auto ui::PageBuilder::Span( std::string_view text ) -> dom::Span*
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


auto ui::PageBuilder::Link( std::string_view text, std::string_view link ) -> dom::Link*
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


auto ui::PageBuilder::Image( std::string_view link ) -> dom::Image*
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


auto ui::PageBuilder::HorizontalRule() -> dom::HorizontalRule*
{
	auto* new_element = AddChild<ui::dom::HorizontalRule>( "hr", {} );

	return new_element;
}


auto ui::PageBuilder::GetParent() -> dom::Element*
{
	if( parent == nullptr ) throw std::runtime_error{ "Missing current element" };
	return parent;
}
