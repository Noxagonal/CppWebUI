module;

#include <drogon/WebSocketConnection.h>

#include "PCH.hpp"

module UI.ClientConnection;


tatzel::ClientConnection::ClientConnection(
	drogon::WebSocketConnectionPtr ws_connection
) :
	ws_connection( ws_connection )
{
	client_dom_tree = std::make_unique<ClientDOMTree>();
	client_updater = std::make_unique<ClientUpdater>( ws_connection );
	page_builder_core = std::make_unique<PageBuilderCore>( *client_dom_tree.get(), *client_updater.get() );
}
