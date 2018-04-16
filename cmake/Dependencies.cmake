find_package(coreutils QUIET)
if(Coreutils_FOUND)
    message("coreutils found : " ${coreutils_INCLUDE_DIRS})
endif()

find_package( OpenCV QUIET )
list(APPEND sdmd_library_dependencies ${OpenCV_LIBS})
