# set configure file with version code
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)
set (VERSION_PATCH 0)
set (VERSION_TWEAK 0)

set(sdmd_version "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}")
message("sdmd_version : " ${sdmd_version})


configure_file (
	"${PROJECT_SOURCE_DIR}/${the_library}/${sdmd_namespace}/sdmd.h.in"
	"${PROJECT_BINARY_DIR}/${the_library}/${sdmd_namespace}/sdmd.h"
)

list(APPEND sdmd_header_files "${PROJECT_BINARY_DIR}/${the_library}/${sdmd_namespace}/sdmd.h")
list(APPEND sdmd_include_directories ${PROJECT_BINARY_DIR}/${the_library})
