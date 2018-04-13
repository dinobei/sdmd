include_directories(${sdmd_include_directories})
add_executable(appSdmdTest main.cpp)
target_link_libraries (appSdmdTest ${the_library})
