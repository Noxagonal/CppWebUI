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


auto ui::PageBuilder::Label( std::string_view text ) -> ui::dom::Label&
{
	auto& new_element = AddChild<ui::dom::Label>( "label", {} );

	new_element.text.OnSet( [this, &new_element]( const std::string& in ){ client_updater->SetText( new_element.id, in ); } );
	new_element.text = std::string{ text };

	return new_element;
}


auto ui::PageBuilder::Container( std::function<void()>&& child_builder_fn ) -> ui::dom::Container&
{
	auto& new_element = AddChild<ui::dom::Container>( "div", {} );

	GoToChild( new_element );
	child_builder_fn();
	GoToParent();

	return new_element;
}


auto ui::PageBuilder::Button( std::string_view text, std::function<void()>&& on_click ) -> dom::Button&
{
	auto& new_element = AddChild<ui::dom::Button>( "button", {} );

	new_element.text = std::string{ text };
	client_updater->SetText( new_element.id, text );

	new_element.on_click = std::move( on_click );
	client_updater->SetOnClick( new_element.id );

	return new_element;
}


auto ui::PageBuilder::GetCurrentElement() -> dom::Element&
{
	if( current_element == nullptr ) throw std::runtime_error{ "Missing current element" };
	return *current_element;
}


auto ui::PageBuilder::GoToChild( const ui::dom::Element& child_element ) -> dom::Element&
{
	auto& elem = GetCurrentElement();
	auto it = std::ranges::find_if( current_element->children, [ &child_element ]( auto& i ){
		return i->id == child_element.id;
	} );
	if( it == current_element->children.end() ) throw std::runtime_error{ "Child not found" };
	current_element = ( *it ).get();
	return *current_element;
}


auto ui::PageBuilder::GoToParent() -> dom::Element&
{
	if( current_element->parent == nullptr )
	{
		current_element = std::addressof( dom_tree->root );
		return *current_element;
	}
	current_element = current_element->parent;
	return *current_element;
}
