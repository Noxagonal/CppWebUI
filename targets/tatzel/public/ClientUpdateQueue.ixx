module;

#include <chrono>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

export module UI.ClientUpdateQueue;

import UI.ClientUpdater;


namespace tatzel {


export
class ClientUpdateQueue
{
public:
	ClientUpdateQueue( ClientUpdater& client_updater ) :
		client_updater{ &client_updater }
	{}

	ClientUpdateQueue( const ClientUpdateQueue& ) = delete;
	ClientUpdateQueue( ClientUpdateQueue&& ) = default;
	~ClientUpdateQueue() = default;

	auto operator=( const ClientUpdateQueue& ) -> ClientUpdateQueue& = delete;
	auto operator=( ClientUpdateQueue&& ) -> ClientUpdateQueue& = default;

	auto SetText( std::string_view id, std::string_view text ) -> void
	{
		pending_text_updates.insert_or_assign( std::string{ id }, std::string{ text } );
	}

	auto SetAttribute(
		std::string_view id,
		std::string_view attribute,
		std::string_view value
	) -> void
	{
		auto key = AttributeKey{
			.id = std::string{ id },
			.attribute = std::string{ attribute }
		};
		pending_attribute_updates.insert_or_assign( std::move( key ), std::string{ value } );
	}

	auto SetModalOpen( std::string_view id, bool open ) -> void
	{
		pending_modal_updates.insert_or_assign( std::string{ id }, open );
	}

	auto HasPendingUpdates() const noexcept -> bool
	{
		return
			!pending_text_updates.empty() ||
			!pending_attribute_updates.empty() ||
			!pending_modal_updates.empty();
	}

	// Call from the page/session update loop. Repeated changes to the same
	// property are coalesced and only the latest value is sent.
	auto Flush() -> void
	{
		if( !client_updater ) return;

		for( const auto& [id, text] : pending_text_updates )
			client_updater->SetText( id, text );

		for( const auto& [key, value] : pending_attribute_updates )
			client_updater->SetAttribute( key.id, key.attribute, value );

		for( const auto& [id, open] : pending_modal_updates )
			client_updater->SetModalOpen( id, open );

		pending_text_updates.clear();
		pending_attribute_updates.clear();
		pending_modal_updates.clear();
	}

private:
	struct AttributeKey
	{
		std::string id;
		std::string attribute;

		auto operator==( const AttributeKey& ) const -> bool = default;
	};

	struct AttributeKeyHash
	{
		auto operator()( const AttributeKey& key ) const noexcept -> size_t
		{
			auto id_hash = std::hash<std::string>{}( key.id );
			auto attribute_hash = std::hash<std::string>{}( key.attribute );
			return id_hash ^ ( attribute_hash << 1 );
		}
	};

	ClientUpdater* client_updater = nullptr;
	std::unordered_map<std::string, std::string> pending_text_updates;
	std::unordered_map<AttributeKey, std::string, AttributeKeyHash> pending_attribute_updates;
	std::unordered_map<std::string, bool> pending_modal_updates;
};


}