module;

#include <json/json.h>

#include <filesystem>
#include <string>
#include <string_view>

export module UI.Utility;


namespace ui {


export
auto GetTemplateDocument( std::filesystem::path path ) -> std::string;

export
auto ParseJson( std::string_view text ) -> Json::Value;

export
auto JsonToString( const Json::Value& json ) -> std::string;

export
auto GenerateUUID() -> std::string;


}
