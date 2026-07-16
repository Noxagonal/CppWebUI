module;

#include "PCH.hpp"

export module UI.ClientDOMTree;

import UI.DOM.Element;


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

	template<typename ElementT = dom::Element>
	auto FindElementById( std::string_view id ) -> ElementT*
	{
		auto RecursiveSearch = [id](this auto& self, dom::Element& element) -> dom::Element*
		{
			if( element.id == id ) return &element;
			for( auto& child : element.GetChildren() )
			{
				auto found = self( *child );
				if( found ) return found;
			}
			return nullptr;
		};

		return dynamic_cast<ElementT*>( RecursiveSearch( root ) );
	}

	dom::Element root;
};


}
