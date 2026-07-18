module;

#include <json/json.h>
#include <drogon/WebSocketController.h>

#include "PCH.hpp"

module UI.ClientUpdater;

import UI.Utility;


tatzel::ClientUpdater::ClientUpdater(
	drogon::WebSocketConnectionPtr ws_connection
) :
	ws_connection( ws_connection )
{}


auto tatzel::ClientUpdater::CreateElement( std::string_view parent_id, std::string_view id, std::string_view tag ) -> void
{
	auto json = CreateJSONOp( "create_element", id );
	json[ "parent_id" ] = std::string{ parent_id };
	json[ "tag" ] = std::string{ tag };
	SendJSON( json );
}


auto tatzel::ClientUpdater::RemoveElement( std::string_view id ) -> void
{
	SendJSON( CreateJSONOp( "remove_element", id ) );
}


auto tatzel::ClientUpdater::SetTag( std::string_view id, std::string_view tag ) -> void
{
	auto json = CreateJSONOp( "set_tag", id );
	json[ "tag" ] = std::string{ tag };
	SendJSON( json );
}


auto tatzel::ClientUpdater::SetAttribute( std::string_view id, std::string_view attribute, std::string_view attribute_value ) -> void
{
	auto json = CreateJSONOp( "set_attribute", id );
	json[ "attribute" ] = std::string{ attribute };
	json[ "attribute_value" ] = std::string{ attribute_value };
	SendJSON( json );
}


auto tatzel::ClientUpdater::SetText( std::string_view id, std::string_view text ) -> void
{
	auto json = CreateJSONOp( "set_text", id );
	json[ "text" ] = std::string{ text };
	SendJSON( json );
}


auto tatzel::ClientUpdater::SetModalOpen( std::string_view id, bool open ) -> void
{
	auto json = CreateJSONOp( "set_modal_open", id );
	json[ "open" ] = open;
	SendJSON( json );
}


auto tatzel::ClientUpdater::SetOnClick( std::string_view id ) -> void
{
	SendJSON( CreateJSONOp( "set_on_click", id ) );
}


auto tatzel::ClientUpdater::SetOnChange( std::string_view id ) -> void
{
	SendJSON( CreateJSONOp( "set_on_change", id ) );
}


auto tatzel::ClientUpdater::SetOnSubmit( std::string_view id ) -> void
{
	SendJSON( CreateJSONOp( "set_on_submit", id ) );
}


auto tatzel::ClientUpdater::CreateJSONOp( std::string_view op, std::string_view id ) -> Json::Value
{
	auto json = Json::Value{};
	json[ "op" ] = std::string{ op };
	json[ "id" ] = std::string{ id };
	return json;
}


auto tatzel::ClientUpdater::SendJSON( const Json::Value& json ) -> void
{
	ws_connection->send( tatzel::JsonToString( json ) );
}