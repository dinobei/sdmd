include_directories(${sdmd_include_directories})
add_executable(appSimpleTest main.cpp)
target_link_libraries (appSimpleTest ${the_library})
