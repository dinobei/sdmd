set(sdmd_source_files)
set(sdmd_header_files)

# list(APPEND sdmd_header_files ijoon/sdmd.h)
add_subdirectory(ijoon/sdmd)

include(${PROJECT_SOURCE_DIR}/cmake/Version.cmake)

list(APPEND sdmd_include_directories ${CMAKE_CURRENT_LIST_DIR})
set(sdmd_include_directories ${sdmd_include_directories} PARENT_SCOPE)

include_directories(${sdmd_include_directories})

if(WIN32)
    add_library(${the_library} SHARED ${sdmd_source_files} ${sdmd_header_files})
else()
    add_library(${the_library} ${sdmd_source_files} ${sdmd_header_files})
endif()
target_link_libraries(${the_library} ${sdmd_library_dependencies})

include(${PROJECT_SOURCE_DIR}/cmake/Install.cmake)

set_property(TARGET ${the_library} PROPERTY VERSION ${sdmd_version})
set_property(TARGET ${the_library} PROPERTY SOVERSION 1)
set_property(TARGET ${the_library} PROPERTY
  INTERFACE_${the_library}_MAJOR_VERSION 0)
set_property(TARGET ${the_library} APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING ${the_library}_MAJOR_VERSION
)
set_property(TARGET ${the_library} PROPERTY INTERFACE_INCLUDE_DIRECTORIES
			${CMAKE_INSTALL_PREFIX}/include)
if(WIN32)
	set_target_properties(${the_library} PROPERTIES COMPILE_FLAGS "/wd4819")
endif()
