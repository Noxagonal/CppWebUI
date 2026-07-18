cmake_minimum_required(VERSION 4.0)

include("${CMAKE_SOURCE_DIR}/cmake/FileOps.cmake")


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
