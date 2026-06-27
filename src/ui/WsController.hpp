#include <drogon/WebSocketController.h>

#include <unordered_set>
#include <mutex>


class WsController : public drogon::WebSocketController<WsController>
{
public:
	static inline std::mutex mutex;
	static inline std::unordered_set<drogon::WebSocketConnectionPtr> connections;

	void handleNewConnection(
		const drogon::HttpRequestPtr& request,
		const drogon::WebSocketConnectionPtr& connection
	) override
	{
		{
			std::lock_guard lock(mutex);
			connections.insert(connection);
		}

		connection->send("Connected");
	}

	void handleConnectionClosed(
		const drogon::WebSocketConnectionPtr& connection
	) override
	{
		std::lock_guard lock(mutex);
		connections.erase(connection);
	}

	void handleNewMessage(
		const drogon::WebSocketConnectionPtr& connection,
		std::string&& message,
		const drogon::WebSocketMessageType& type
	) override
	{
	}

	static void Broadcast(const std::string& message)
	{
		std::lock_guard lock(mutex);

		for(const auto& connection : connections)
		{
			connection->send(message);
		}
	}

	WS_PATH_LIST_BEGIN
		WS_PATH_ADD("/ws");
	WS_PATH_LIST_END
};
