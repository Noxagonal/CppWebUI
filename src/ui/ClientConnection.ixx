module;

#include <drogon/WebSocketConnection.h>

#include "PCH.hpp"

export module UI.ClientConnection;

import UI.ClientDOMTree;
import UI.ClientUpdater;
import UI.PageBuilderCore;
import UI.Page;


namespace ui {


export
class ClientConnection
{
public:
	ClientConnection(
		drogon::WebSocketConnectionPtr ws_connection
	);
	ClientConnection( const ClientConnection& ) = delete;
	ClientConnection( ClientConnection&& ) = default;

	auto operator=( const ClientConnection& ) -> ClientConnection& = delete;
	auto operator=( ClientConnection&& ) -> ClientConnection& = default;

	drogon::WebSocketConnectionPtr ws_connection = nullptr;
	Page* page;
	std::unique_ptr<ClientDOMTree> client_dom_tree;
	std::unique_ptr<ClientUpdater> client_updater;
	std::unique_ptr<PageBuilderCore> page_builder_core;
};


}
