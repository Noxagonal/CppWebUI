module;

export module UI.PageBuilderCore;

import UI.ClientDOMTree;
import UI.ClientUpdater;
import UI.ClientUpdateQueue;
import UI.DOM.Element;


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
		client_updater( &client_updater ),
		client_update_queue( client_updater )
	{
		root_element->AttachUpdateQueue( client_update_queue );
	}

	PageBuilderCore( const PageBuilderCore& ) = delete;
	PageBuilderCore( PageBuilderCore&& ) = delete;
	~PageBuilderCore() = default;

	auto operator=( const PageBuilderCore& ) -> PageBuilderCore& = delete;
	auto operator=( PageBuilderCore&& ) -> PageBuilderCore& = delete;

	inline auto GetDOMTree() { return dom_tree; }
	inline auto GetRootElement() { return root_element; }
	inline auto GetClientUpdater() { return client_updater; }
	inline auto GetClientUpdateQueue() -> ClientUpdateQueue* { return &client_update_queue; }

	// Intended to be called by the page/session loop approximately every 10 ms,
	// or at an explicit synchronization point.
	inline auto FlushClientUpdates() -> void
	{
		client_update_queue.Flush();
	}

private:
	ClientDOMTree* dom_tree = nullptr;
	dom::Element* root_element = nullptr;
	ClientUpdater* client_updater = nullptr;
	ClientUpdateQueue client_update_queue;
};


}