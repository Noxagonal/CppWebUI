module;

#include <json/json.h>
#include <drogon/WebSocketController.h>

module UI.ClientUpdater;

import UI.Utility;


ui::ClientUpdater::ClientUpdater(
	drogon::WebSocketConnectionPtr ws_connection
) :
	ws_connection( ws_connection )
{}


auto ui::ClientUpdater::CreateElement( std::string_view parent_id, std::string_view id, std::string_view tag ) -> void
{
	auto json = Json::Value{};
	json[ "op" ] = "create_element";
	json[ "id" ] = std::string{ id };
	json[ "parent_id" ] = std::string{ parent_id };
	json[ "tag" ] = std::string{ tag };
	SendJSON( json );
}


auto ui::ClientUpdater::SetText( std::string_view id, std::string_view text ) -> void
{
	auto json = Json::Value{};
	json[ "op" ] = "set_text";
	json[ "id" ] = std::string{ id };
	json[ "text" ] = std::string{ text };
	SendJSON( json );
}


auto ui::ClientUpdater::SetOnClick( std::string_view id ) -> void
{
	auto json = Json::Value{};
	json[ "op" ] = "set_on_click";
	json[ "id" ] = std::string{ id };
	SendJSON( json );
}


auto ui::ClientUpdater::SendJSON( const Json::Value& json ) -> void
{
	ws_connection->send( ui::JsonToString( json ) );
}