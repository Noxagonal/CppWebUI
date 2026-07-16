module;

#include <drogon/WebSocketController.h>

#include "PCH.hpp"

export module UI.ClientUpdater;


namespace tatzel {


export
class ClientUpdater
{
public:
	ClientUpdater(
		drogon::WebSocketConnectionPtr ws_connection
	);
	ClientUpdater( const ClientUpdater& ) = delete;
	ClientUpdater( ClientUpdater&& ) = default;
	~ClientUpdater() = default;

	auto operator=( const ClientUpdater& ) -> ClientUpdater& = delete;
	auto operator=( ClientUpdater&& ) -> ClientUpdater& = default;

	auto CreateElement( std::string_view parent_id, std::string_view id, std::string_view tag ) -> void;
	auto RemoveElement( std::string_view id ) -> void;
	auto SetTag( std::string_view id, std::string_view tag ) -> void;
	auto SetAttribute( std::string_view id, std::string_view attribute, std::string_view attribute_value ) -> void;
	auto SetText( std::string_view id, std::string_view text ) -> void;
	auto SetModalOpen( std::string_view id, bool open ) -> void;
	auto SetOnClick( std::string_view id ) -> void;
	auto SetOnChange( std::string_view id ) -> void;
	auto SetOnSubmit( std::string_view id ) -> void;

private:

	auto CreateJSONOp( std::string_view op, std::string_view id ) -> Json::Value;
	auto SendJSON( const Json::Value& json ) -> void;

	drogon::WebSocketConnectionPtr ws_connection;
};


}