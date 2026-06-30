module;

#include <drogon/WebSocketConnection.h>

module UI.ClientConnection;


ui::ClientConnection::ClientConnection(
	drogon::WebSocketConnectionPtr ws_connection
) :
	ws_connection( ws_connection )
{
	client_dom_tree = std::make_unique<ClientDOMTree>();
	client_updater = std::make_unique<ClientUpdater>( ws_connection );
	page_builder = std::make_unique<PageBuilder>( *client_dom_tree.get(), *client_updater.get() );
}
