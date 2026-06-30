module;

#include <drogon/WebSocketController.h>

export module UI.ClientUpdater;


namespace ui {


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
	auto SetText( std::string_view id, std::string_view text ) -> void;
	auto SetOnClick( std::string_view id ) -> void;

private:

	auto SendJSON( const Json::Value& json ) -> void;

	drogon::WebSocketConnectionPtr ws_connection;
};


}