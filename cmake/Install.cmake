set(INSTALL_INCLUDE_DESTINATION include/${sdmd_namespace}/${the_library})
install (TARGETS
          ${the_library}
        EXPORT
          ExportTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
		INCLUDES DESTINATION ${INSTALL_INCLUDE_DESTINATION})

install (FILES
          ${sdmd_header_files}
        DESTINATION
          ${INSTALL_INCLUDE_DESTINATION})


include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/cmake.in/${the_library}ConfigVersion.cmake"
  VERSION ${sdmd_version}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT ExportTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake.in/${the_library}Targets.cmake"
  NAMESPACE ${sdmd_namespace}::
)
configure_file(${PROJECT_SOURCE_DIR}/cmake/${the_library}Config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/cmake.in/${the_library}Config.cmake"
  COPYONLY
)

set(ConfigPackageLocation lib/cmake/${the_library})
install(EXPORT ExportTargets
  FILE
    ${the_library}Targets.cmake
  NAMESPACE
    ${sdmd_namespace}::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    cmake/${the_library}Config.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/cmake.in/${the_library}ConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation})


if(sdmd_EXTR_DIST_FILES)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	if(WIN32)
		set(EXTR_ROOT_DIR ${the_library}_$<CONFIG>_$(Platform)_v${sdmd_version})
		set(EXTR_LIB_NAME ${the_library}.lib)
		set(EXTR_BIN_NAME ${the_library}.dll)
		add_custom_command(TARGET ${the_library}
						   POST_BUILD
						   COMMAND ${CMAKE_COMMAND} -E copy_if_different
						   					${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${EXTR_BIN_NAME}
											${CMAKE_BINARY_DIR}/${EXTR_ROOT_DIR}/bin/${EXTR_BIN_NAME}
						   COMMAND ${CMAKE_COMMAND} -E copy_if_different
						   					${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${EXTR_LIB_NAME}
											${CMAKE_BINARY_DIR}/${EXTR_ROOT_DIR}/lib/${EXTR_LIB_NAME}
						   COMMAND ${CMAKE_COMMAND} -E make_directory
 						   					${CMAKE_BINARY_DIR}/${EXTR_ROOT_DIR}/include/${sdmd_namespace}/${the_library}
						   COMMAND ${CMAKE_COMMAND} -E copy
						   					${sdmd_header_files}
											${CMAKE_BINARY_DIR}/${EXTR_ROOT_DIR}/include/${sdmd_namespace}/${the_library}
						   COMMENT "Extract distribution files")
    elseif(APPLE)
		set(EXTR_ROOT_DIR ${the_library}_macos_v${sdmd_version})
		set(EXTR_BIN_NAME lib${the_library}.a)
		add_custom_command(TARGET ${the_library}
						   POST_BUILD
						   COMMAND ${CMAKE_COMMAND} -E copy_if_different
						   					${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${EXTR_BIN_NAME}
											${CMAKE_BINARY_DIR}/${EXTR_ROOT_DIR}/bin/${EXTR_BIN_NAME}
						   COMMAND ${CMAKE_COMMAND} -E make_directory
						   					${CMAKE_BINARY_DIR}/${EXTR_ROOT_DIR}/include/${sdmd_namespace}/${the_library}
						   COMMAND ${CMAKE_COMMAND} -E copy
						   					${sdmd_header_files}
											${CMAKE_BINARY_DIR}/${EXTR_ROOT_DIR}/include/${sdmd_namespace}/${the_library}
						   COMMENT "Extract distribution files")
    else()
		set(EXTR_ROOT_DIR ${the_library}_linux_v${sdmd_version})
		set(EXTR_BIN_NAME lib${the_library}.a)
		add_custom_command(TARGET ${the_library}
						   POST_BUILD
						   COMMAND ${CMAKE_COMMAND} -E copy_if_different
						    				${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXTR_BIN_NAME}
											${CMAKE_BINARY_DIR}/${EXTR_ROOT_DIR}/bin/${EXTR_BIN_NAME}
						   COMMAND ${CMAKE_COMMAND} -E make_directory
 						   					${CMAKE_BINARY_DIR}/${EXTR_ROOT_DIR}/include/${sdmd_namespace}/${the_library}
 						   COMMAND ${CMAKE_COMMAND} -E copy
 						   					${sdmd_header_files}
				 							${CMAKE_BINARY_DIR}/${EXTR_ROOT_DIR}/include/${sdmd_namespace}/${the_library}
						   COMMENT "Extract distribution files")
	endif()
endif()
