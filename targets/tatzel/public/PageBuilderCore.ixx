module;

export module UI.PageBuilderCore;

import UI.ClientDOMTree;
import UI.ClientUpdater;
import UI.UI.Element;


namespace tatzel {


export
class PageBuilderCore
{
public:
	inline PageBuilderCore(
		ClientDOMTree& dom_tree,
		ClientUpdater& client_updater
	) :
		dom_tree( &dom_tree ),
		root_element( &dom_tree.root ),
		client_updater( &client_updater )
	{}

	PageBuilderCore( const PageBuilderCore& ) = default;
	~PageBuilderCore() = default;

	auto operator=( const PageBuilderCore& ) -> PageBuilderCore& = default;

	inline auto GetDOMTree() { return dom_tree; }
	inline auto GetRootElement() { return root_element; }
	inline auto GetClientUpdater() { return client_updater; }

private:
	ClientDOMTree* dom_tree = nullptr;
	dom::Element* root_element = nullptr;
	ClientUpdater* client_updater = nullptr;
};


}
