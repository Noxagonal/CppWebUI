module;

#include <string_view>

export module UI.ClientDOMTree;

import UI.UI.LogicalElement;


namespace tatzel {


export
class ClientDOMTree
{
public:
	ClientDOMTree();
	ClientDOMTree( const ClientDOMTree& ) = delete;
	ClientDOMTree( ClientDOMTree&& ) = default;
	~ClientDOMTree();

	auto operator=( const ClientDOMTree& ) -> ClientDOMTree& = delete;
	auto operator=( ClientDOMTree&& ) -> ClientDOMTree& = default;

	template<typename ElementT>
	auto FindElementById( std::string_view id ) -> ElementT*
	{
		auto RecursiveSearch = [id](this auto& self, ui::LogicalElement& element) -> ui::LogicalElement*
		{
			if( element.GetID() == id ) return &element;
			for( const auto& child : element.GetChildren() )
			{
				auto found = self( *child );
				if( found ) return found;
			}
			return nullptr;
		};

		return dynamic_cast<ElementT*>( RecursiveSearch( root ) );
	}

	ui::LogicalElement root;
};


}
