module;

#include <string_view>
#include <functional>
#include <stdexcept>

module UI.PageBuilder;


ui::PageBuilder::PageBuilder( ui::ClientDOMTree& dom_tree, ui::ClientUpdater& client_updater )
{
	this->dom_tree = &dom_tree;
	this->current_element = std::addressof( this->dom_tree->root );

	this->client_updater = &client_updater;
}


auto ui::PageBuilder::Label( std::string_view text ) -> ui::dom::Label*
{
	auto* new_element = AddChild<ui::dom::Label>( "label", {} );

	new_element->text.OnSet(
		[this, new_element]( const std::string& in )
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

	new_element->text.OnSet(
		[this, new_element]( const std::string& in )
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

	new_element->text.OnSet(
		[this, new_element]( const std::string& in )
		{
			client_updater->SetText( new_element->id, in );
		}
	);

	new_element->heading_style.OnSet(
		[this, new_element]( const dom::HeadingStyle& in )
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

	new_element->text.OnSet(
		[this, new_element]( const std::string& in )
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

	new_element->text.OnSet(
		[this, new_element]( const std::string& in )
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

	new_element->text.OnSet(
		[this, new_element]( const std::string& in )
		{
			client_updater->SetText( new_element->id, in );
		}
	);

	new_element->href.OnSet(
		[this, new_element]( const std::string& in )
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

	new_element->src.OnSet(
		[this, new_element]( const std::string& in )
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


auto ui::PageBuilder::GetCurrentElement() -> dom::Element*
{
	if( current_element == nullptr ) throw std::runtime_error{ "Missing current element" };
	return current_element;
}


auto ui::PageBuilder::GoToChild( const ui::dom::Element* child_element ) -> dom::Element*
{
	auto* elem = GetCurrentElement();
	auto it = std::ranges::find_if( current_element->children, [ &child_element ]( auto& i ){
		return i->id == child_element->id;
	} );
	if( it == current_element->children.end() ) throw std::runtime_error{ "Child not found" };
	current_element = ( *it ).get();
	return current_element;
}


auto ui::PageBuilder::GoToParent() -> dom::Element*
{
	if( current_element->parent == nullptr )
	{
		current_element = std::addressof( dom_tree->root );
		return current_element;
	}
	current_element = current_element->parent;
	return current_element;
}
