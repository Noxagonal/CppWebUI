cmake_minimum_required(VERSION 4.0)

project(Tatzel LANGUAGES CXX)


# Helper to collect files by extension
function(collect_files_by_extension
	OUTPUT_VAR
	BASE_DIR
	EXTENSIONS
)
	set(_FILES "")
	foreach(_CURRENT_EXT IN LISTS EXTENSIONS)
		file(GLOB_RECURSE _TMP
			CONFIGURE_DEPENDS
			"${BASE_DIR}/*.${_CURRENT_EXT}"
		)
		list(APPEND _FILES ${_TMP})
	endforeach()

	# Quote to preserve list semantics even if paths contain spaces.
	set(${OUTPUT_VAR} "${_FILES}" PARENT_SCOPE)
endfunction()


find_program(NODE_EXECUTABLE node REQUIRED)
find_program(NPM_EXECUTABLE npm REQUIRED)
find_program(NPX_EXECUTABLE npx REQUIRED)

message(STATUS "Found node: ${NODE_EXECUTABLE}")
message(STATUS "Found npm: ${NPM_EXECUTABLE}")
message(STATUS "Found npx: ${NPX_EXECUTABLE}")

set(NPM_STAMP_FILE "${CMAKE_BINARY_DIR}/npm_install.stamp")
set(TYPESCRIPT_STAMP_FILE "${CMAKE_BINARY_DIR}/typescript_build.stamp")

file(GLOB_RECURSE TYPESCRIPT_SOURCE_FILES
	CONFIGURE_DEPENDS
	"${CMAKE_SOURCE_DIR}/src/ts/*.ts"
	"${CMAKE_SOURCE_DIR}/src/ts/*.tsx"
)

add_custom_command(
	OUTPUT "${NPM_STAMP_FILE}"
	COMMAND "${NPM_EXECUTABLE}" ci
	COMMAND "${CMAKE_COMMAND}" -E touch "${NPM_STAMP_FILE}"
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	DEPENDS
		"${CMAKE_SOURCE_DIR}/package.json"
		"${CMAKE_SOURCE_DIR}/package-lock.json"
	COMMENT "Installing npm dependencies"
	VERBATIM
	USES_TERMINAL
)

add_custom_target(
	npm_install
	DEPENDS "${NPM_STAMP_FILE}"
)

add_custom_command(
	OUTPUT "${TYPESCRIPT_STAMP_FILE}"
	COMMAND "${NPM_EXECUTABLE}" run build
	COMMAND "${CMAKE_COMMAND}" -E touch "${TYPESCRIPT_STAMP_FILE}"
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	DEPENDS
		"${NPM_STAMP_FILE}"
		"${CMAKE_SOURCE_DIR}/package.json"
		"${CMAKE_SOURCE_DIR}/package-lock.json"
		"${CMAKE_SOURCE_DIR}/tsconfig.json"
		${TYPESCRIPT_SOURCE_FILES}
	COMMENT "Compiling TypeScript"
	VERBATIM
	USES_TERMINAL
)

add_custom_target(
	typescript_build
	DEPENDS "${TYPESCRIPT_STAMP_FILE}"
)


set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Keep the initial build smaller.
# You can turn these back ON later if you need them.
set(BUILD_CTL OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_ORM OFF CACHE BOOL "" FORCE)
set(BUILD_BROTLI OFF CACHE BOOL "" FORCE)
set(BUILD_YAML_CONFIG OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
	drogon
	GIT_REPOSITORY https://github.com/drogonframework/drogon.git
	GIT_TAG v1.9.13
	GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(drogon)

set(_SOURCE_EXTENSIONS
	c cpp c hpp
)
set(_MODULE_EXTENSIONS
	ixx cppm
)

# Public source files
collect_files_by_extension(_PUBLIC_SOURCE_FILES
	"${PROJECT_SOURCE_DIR}/include/"
	"${_SOURCE_EXTENSIONS}"
)

# Private source files
collect_files_by_extension(_PRIVATE_SOURCE_FILES
	"${PROJECT_SOURCE_DIR}/src/"
	"${_SOURCE_EXTENSIONS}"
)

# Public module files
collect_files_by_extension(_PUBLIC_MODULE_FILES
	"${PROJECT_SOURCE_DIR}/include/"
	"${_MODULE_EXTENSIONS}"
)

# Private module files
collect_files_by_extension(_PRIVATE_MODULE_FILES
	"${PROJECT_SOURCE_DIR}/src/"
	"${_MODULE_EXTENSIONS}"
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
	FILES
		${_PUBLIC_SOURCE_FILES}
		${_PRIVATE_SOURCE_FILES}
		${_PUBLIC_MODULE_FILES}
		${_PRIVATE_MODULE_FILES}
)


add_executable(${PROJECT_NAME})

# Set target primary source files.
if(NOT "${_PUBLIC_SOURCE_FILES}" STREQUAL "")
	target_sources(${PROJECT_NAME}
		PUBLIC
			${_PUBLIC_SOURCE_FILES}
	)
endif()
if(NOT "${_PRIVATE_SOURCE_FILES}" STREQUAL "")
	target_sources(${PROJECT_NAME}
		PRIVATE
			${_PRIVATE_SOURCE_FILES}
	)
endif()

# Set target module source files.
if(NOT "${_PUBLIC_MODULE_FILES}" STREQUAL "")
	target_sources(${PROJECT_NAME}
		PUBLIC
			FILE_SET cxx_public_modules
				TYPE CXX_MODULES
				BASE_DIRS ${PROJECT_SOURCE_DIR}
				FILES ${_PUBLIC_MODULE_FILES}
	)
endif()
if(NOT "${_PRIVATE_MODULE_FILES}" STREQUAL "")
	target_sources(${PROJECT_NAME}
		PRIVATE
			FILE_SET cxx_private_modules
				TYPE CXX_MODULES
				BASE_DIRS ${PROJECT_SOURCE_DIR}
				FILES ${_PRIVATE_MODULE_FILES}
	)
endif()

target_precompile_headers(${PROJECT_NAME}
	PRIVATE
		"${PROJECT_SOURCE_DIR}/src/ui/PCH.hpp"
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Drogon::Drogon
)

add_dependencies(${PROJECT_NAME}
	typescript_build
)
