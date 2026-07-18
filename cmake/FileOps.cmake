
include_guard(GLOBAL)


# Collect all files in a directory tree with the given extensions.
#
# Example:
# collect_files_by_extension(_SOURCE_FILES
#     "${CMAKE_CURRENT_SOURCE_DIR}"
#     c cpp h hpp
# )
function(collect_files_by_extension
	OUTPUT_VAR
	BASE_DIR
)
	if(ARGC LESS 3)
		message(FATAL_ERROR
			"collect_files_by_extension requires an output variable, "
			"a base directory, and at least one extension."
		)
	endif()

	set(_FILES)

	foreach(_CURRENT_EXT IN LISTS ARGN)
		# Permit extensions to be supplied as either "cpp" or ".cpp".
		string(REGEX REPLACE "^\\." "" _CURRENT_EXT "${_CURRENT_EXT}")

		file(GLOB_RECURSE _MATCHING_FILES
			CONFIGURE_DEPENDS
			"${BASE_DIR}/*.${_CURRENT_EXT}"
		)

		list(APPEND _FILES ${_MATCHING_FILES})
	endforeach()

	list(REMOVE_DUPLICATES _FILES)
	list(SORT _FILES)

	set(${OUTPUT_VAR} "${_FILES}" PARENT_SCOPE)
endfunction()


# Collect ordinary C and C++ source/header files from a directory tree.
function(collect_source_files
	OUTPUT_VAR
	BASE_DIR
)
	collect_files_by_extension(_FILES
		"${BASE_DIR}"
		c cpp h hpp
	)

	set(${OUTPUT_VAR} "${_FILES}" PARENT_SCOPE)
endfunction()


# Collect C++ module interface files from a directory tree.
function(collect_module_files
	OUTPUT_VAR
	BASE_DIR
)
	collect_files_by_extension(_FILES
		"${BASE_DIR}"
		ixx cppm
	)

	set(${OUTPUT_VAR} "${_FILES}" PARENT_SCOPE)
endfunction()
