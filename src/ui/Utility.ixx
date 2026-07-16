module;

#include <json/json.h>

#include "PCH.hpp"

export module UI.Utility;


namespace tatzel {


export
auto GetTemplateDocument( std::filesystem::path path ) -> std::string;

export
auto ParseJson( std::string_view text ) -> Json::Value;

export
auto JsonToString( const Json::Value& json ) -> std::string;

export
auto GenerateUUID() -> std::string;


}
