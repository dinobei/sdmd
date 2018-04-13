cmake_minimum_required (VERSION 3.8)
set(the_library sdmd)
set (sdmd_namespace ijoon) # (sdmd) sigma delta modetion detection
project (${the_library})

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(sdmd_include_directories)

include(cmake/PlatformSpecific.cmake)
include(cmake/Utils.cmake)
include(cmake/Dependencies.cmake)

option (sdmd_EXTR_DIST_FILES "Extract distribution files" FALSE)

add_subdirectory(${the_library})

option (sdmd_BUILD_APPS "Build example apps" TRUE)
if(sdmd_BUILD_APPS)
    add_subdirectory(apps)
endif()
