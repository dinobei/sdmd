file(GLOB_RECURSE local_header_files *.h)
file(GLOB_RECURSE local_source_files *.cpp)

list(APPEND sdmd_source_files ${local_source_files})
list(APPEND sdmd_header_files ${local_header_files})

set(sdmd_source_files ${sdmd_source_files} PARENT_SCOPE)
set(sdmd_header_files ${sdmd_header_files} PARENT_SCOPE)
