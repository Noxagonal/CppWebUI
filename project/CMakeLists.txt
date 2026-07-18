cmake_minimum_required(VERSION 4.0)

include("${CMAKE_SOURCE_DIR}/cmake/FileOps.cmake")


##############################################################
# TypeScript compile target
##############################################################
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

##############################################################
# Tatzel library target
##############################################################
collect_source_files(_PUBLIC_SOURCE_FILES  "${CMAKE_CURRENT_SOURCE_DIR}/public/")
collect_source_files(_PRIVATE_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/private/")
collect_module_files(_PUBLIC_MODULE_FILES  "${CMAKE_CURRENT_SOURCE_DIR}/public/")
collect_module_files(_PRIVATE_MODULE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/private/")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
	FILES
		${_PUBLIC_SOURCE_FILES}
		${_PRIVATE_SOURCE_FILES}
		${_PUBLIC_MODULE_FILES}
		${_PRIVATE_MODULE_FILES}
)

add_library(Tatzel STATIC)

# Set target primary source files.
if(NOT "${_PUBLIC_SOURCE_FILES}" STREQUAL "")
	target_sources(Tatzel
		PUBLIC
			${_PUBLIC_SOURCE_FILES}
	)
endif()
if(NOT "${_PRIVATE_SOURCE_FILES}" STREQUAL "")
	target_sources(Tatzel
		PRIVATE
			${_PRIVATE_SOURCE_FILES}
	)
endif()

# Set target module source files.
if(NOT "${_PUBLIC_MODULE_FILES}" STREQUAL "")
	target_sources(Tatzel
		PUBLIC
			FILE_SET cxx_public_modules
				TYPE CXX_MODULES
				BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
				FILES ${_PUBLIC_MODULE_FILES}
	)
endif()
if(NOT "${_PRIVATE_MODULE_FILES}" STREQUAL "")
	target_sources(Tatzel
		PRIVATE
			FILE_SET cxx_private_modules
				TYPE CXX_MODULES
				BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
				FILES ${_PRIVATE_MODULE_FILES}
	)
endif()

target_precompile_headers(Tatzel
	PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/private/PCH.hpp"
)

target_link_libraries(Tatzel
	PRIVATE
		Drogon::Drogon
)

add_dependencies(Tatzel
	typescript_build
)
