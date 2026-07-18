cmake_minimum_required(VERSION 4.0)


##############################################################
# TypeScript compilation targets
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
