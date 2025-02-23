# --- Project ---

cmake_minimum_required(VERSION 3.30)

set(PROJECT_NAME "PapyrusCommonLibrary")
set(PROJECT_AUTHOR "SoleVaultBoy")
set(PROJECT_VERSION 1.6.1.0)
set(PROJECT_LICENSE "MIT License")
set(PROJECT_DESCRIPTION "${PROJECT_NAME}")

project(
	"${PROJECT_NAME}"
	VERSION "${PROJECT_VERSION}"
	DESCRIPTION "${PROJECT_DESCRIPTION}"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF)
set(CMAKE_OPTIMIZE_DEPENDENCIES ON)

set(BOOST_REGEX_STANDALONE ON)

# --- Options ---

set(ENABLE_FALLOUT_F4 ON)
set(ENABLE_FALLOUT_NG ON)
set(ENABLE_FALLOUT_VR OFF)

set(F4SE_SUPPORT_XBYAK OFF)
set(REX_OPTION_INI ON)
set(REX_OPTION_JSON OFF)
set(REX_OPTION_TOML OFF)

option(COPY_BUILD_TO_PARENT "Copy the built to the parent directory" ON)
option(COPY_BUILD_TO_F4SE "Copy the built to F4SE's plugin directory" OFF)

# --- Output Path ---

if(COPY_BUILD_TO_PARENT AND COPY_BUILD_TO_F4SE)
	message(FATAL_ERROR "COPY_BUILD_TO_F4SE and COPY_BUILD_TO_PARENT should not be enabled at the same time.")
endif()

if (COPY_BUILD_TO_PARENT)
	set(OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/..")
elseif(COPY_BUILD_TO_F4SE)
	if (NOT DEFINED FO4_ROOT AND NOT DEFINED ENV{FO4_ROOT})
		message(FATAL_ERROR "The environment variable FO4_ROOT is not set.")
	endif()

	set(FO4_ROOT "$ENV{FO4_ROOT}" CACHE STRING "")
	set(OUTPUT_PATH "${FO4_ROOT}/Data/F4SE/Plugins")
endif()

# --- Add Dependencies ---

find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# --- Add Sources ---

file(
	GLOB_RECURSE
	SOURCES
	CONFIGURE_DEPENDS
		"${CMAKE_CURRENT_SOURCE_DIR}/include/*"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*"
)

list(
	REMOVE_ITEM
	SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/include/PCH.hpp"
)

set(PLUGIN_HEADER
	"${CMAKE_CURRENT_BINARY_DIR}/include/Plugin.hpp"
)

set(VERSION_HEADER
	"${CMAKE_CURRENT_BINARY_DIR}/Version.rc"
)

source_group(
	TREE "${CMAKE_CURRENT_SOURCE_DIR}"
	FILES "${SOURCES}"
)

source_group(
	TREE "${CMAKE_CURRENT_BINARY_DIR}"
	FILES "${PLUGIN_HEADER}"
)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/Plugin.hpp.in"
	"${PLUGIN_HEADER}"
	@ONLY
)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/Version.rc.in"
	"${VERSION_HEADER}"
	@ONLY
)

# --- Include ---

if(NOT TARGET boost_regex)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/extern/boost-regex" boost_regex)
endif()

if(NOT TARGET CommonLibF4)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/extern/CommonLibF4" CommonLibF4)
endif()

add_library(
	"${PROJECT_NAME}"
	SHARED
		"${SOURCES}"
		"${PLUGIN_HEADER}"
		"${VERSION_HEADER}"
)

target_include_directories(
	"${PROJECT_NAME}"
	PRIVATE
		"${CMAKE_CURRENT_BINARY_DIR}/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_precompile_headers(
	"${PROJECT_NAME}"
	PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/include/PCH.hpp"
)

# --- Compile ---

target_compile_definitions(
	"${PROJECT_NAME}"
	PRIVATE
		SI_NO_CONVERSION
)

# --- Link ---

target_link_libraries(
	"${PROJECT_NAME}"
	PRIVATE
		CommonLibF4::CommonLibF4
		fmt::fmt
		nlohmann_json::nlohmann_json
		Boost::regex
)

# --- Copy Output ---

if(DEFINED OUTPUT_PATH)
	add_custom_command(
		TARGET "${PROJECT_NAME}"
		POST_BUILD
			COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:${PROJECT_NAME}>" "${OUTPUT_PATH}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
			COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_PDB_FILE:${PROJECT_NAME}>" "${OUTPUT_PATH}/$<TARGET_PDB_FILE_NAME:${PROJECT_NAME}>"
	)
endif()
