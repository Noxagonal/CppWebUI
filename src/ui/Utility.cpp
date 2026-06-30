module;

#include <json/json.h>
#include <drogon/utils/Utilities.h>

#include <filesystem>
#include <string>
#include <string_view>
#include <fstream>
#include <sstream>

module UI.Utility;


auto ui::GetTemplateDocument( std::filesystem::path path ) -> std::string
{
	if( !std::filesystem::is_regular_file( path ) ) throw std::runtime_error{ "Template file does not exist" };

	auto template_file = std::ifstream{};
	template_file.open( path, std::ios::ate );

	if( !template_file.is_open() ) throw std::runtime_error{ "Could not read template file" };

	auto file_size = int64_t( template_file.tellg() );
	if( file_size == 0 ) throw std::runtime_error{ "Template file is empty" };
	template_file.seekg( 0 );

	auto ret = std::string( file_size, '\0' );
	template_file.read( ret.data(), file_size );

	return ret;
}


auto ui::ParseJson( std::string_view text ) -> Json::Value
{
	Json::CharReaderBuilder builder;
	Json::Value root;
	std::string errors;

	std::istringstream stream{ std::string{ text } };

	auto success = Json::parseFromStream(
		builder,
		stream,
		&root,
		&errors
	);

	if( !success ) throw std::runtime_error{ "Failed to parse JSON string" };

	return root;
}


auto ui::JsonToString( const Json::Value& json ) -> std::string
{
	Json::StreamWriterBuilder writer;
	writer[ "indentation" ] = ""; // compact JSON, no pretty-printing

	return Json::writeString( writer, json );
}


auto ui::GenerateUUID() -> std::string
{
	return drogon::utils::getUuid();
}
