module;

#include <drogon/WebSocketController.h>

#include <vector>
#include <mutex>

export module UI.WSController;

import UI.Utility;
import UI.ClientConnection;
import UI.App;

import UI.DOM.Button;


export
class WsController : public drogon::WebSocketController<WsController>
{
public:
	static inline std::mutex mutex;
	static inline std::vector<ui::ClientConnection> connections;

	void handleNewConnection(
		const drogon::HttpRequestPtr& request,
		const drogon::WebSocketConnectionPtr& ws_connection
	) override
	{
		CreateClientConnection( ws_connection );

		ws_connection->send( R"({"type":"ok","message":"Connected"})" );
	}

	void handleConnectionClosed(
		const drogon::WebSocketConnectionPtr& ws_connection
	) override
	{
		EraseClientConnection( ws_connection );
	}

	void handleNewMessage(
		const drogon::WebSocketConnectionPtr& ws_connection,
		std::string&& message,
		const drogon::WebSocketMessageType& type
	) override
	{
		// Only accept text.
		if( type != drogon::WebSocketMessageType::Text ) return;

		auto client_connection = FindClientConnection( ws_connection );
		if( !client_connection )
		{
			ws_connection->send( R"({"type":"error","message":"Session expired, please reconnect"})" );
			return;
		}

		auto json = ui::ParseJson( message );
		if( json[ "op" ] == "connect" )
		{
			// Handle new connection.
			auto route_path = json[ "route_path" ].asString();
			auto* page = ui::GetGlobalApp().FindRegisteredPage( route_path );

			if( page == nullptr )
			{
				ws_connection->send( R"({"type":"error","message":"Page not found"})" );
				return;
			}
			client_connection->page = page;

			// Build initial page contents.
			client_connection->page->page_builder_fn( *client_connection->page_builder );

			return;
		}

		// not a connection type message,
		if( json[ "op" ] == "button_clicked" )
		{
			auto button_id = json[ "id" ].asString();
			auto button = client_connection->client_dom_tree->FindElementById<ui::dom::Button>( button_id );
			if( button ) button->on_click();
			return;
		}
	}

	static auto Broadcast( const std::string& message ) -> void
	{
		std::lock_guard lock(mutex);

		for(const auto& connection : connections)
		{
			connection.ws_connection->send( message );
		}
	}

private:

	static auto EraseClientConnection( const drogon::WebSocketConnectionPtr& ws_connection ) -> void
	{
		std::lock_guard lock( mutex );
		auto it = std::ranges::find_if( connections, [ &ws_connection ]( auto& c ){
			return c.ws_connection == ws_connection;
		});
		if( it == connections.end() ) return;
		connections.erase( it );
	}

	static auto CreateClientConnection( const drogon::WebSocketConnectionPtr& ws_connection ) -> ui::ClientConnection*
	{
		std::lock_guard lock( mutex );
		connections.push_back(
			ui::ClientConnection{
				ws_connection
			}
		);
		return &connections.back();
	}

	static auto FindClientConnection( const drogon::WebSocketConnectionPtr& ws_connection ) -> ui::ClientConnection*
	{
		std::lock_guard lock( mutex );
		auto it = std::ranges::find_if( connections, [&ws_connection]( auto& c ){ return c.ws_connection == ws_connection; } );
		if( it == connections.end() ) return nullptr;
		return &*it;
	}

public:
	WS_PATH_LIST_BEGIN
		WS_PATH_ADD("/ws");
	WS_PATH_LIST_END
};
