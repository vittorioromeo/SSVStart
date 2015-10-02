# Add a custom target for the unit tests.
add_custom_target(tests COMMENT "Build all the unit tests.")

# `check` depends on `tests`.
add_dependencies(check tests)

# Glob all tests.
file(GLOB_RECURSE SSVS_TEST_SOURCES "*.cpp")

# Include directories.
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})

# Add all the unit tests.
foreach(_file IN LISTS SSVS_TEST_SOURCES)
    file(READ "${_file}" _contents)
    vrm_cmake_target_name_for(_target "${_file}")
    message("\nPORCO DIO\n ${_target} \n\n${${PROJECT_NAME_UPPER}_SOURCE_DIR}\n\n\n")

    add_executable(${_target} EXCLUDE_FROM_ALL "${_file}")

    target_link_libraries(${_target} ${SFML_AUDIO_LIBRARY_RELEASE})
    target_link_libraries(${_target} ${SFML_GRAPHICS_LIBRARY_RELEASE})
    target_link_libraries(${_target} ${SFML_WINDOW_LIBRARY_RELEASE})
    target_link_libraries(${_target} ${SFML_SYSTEM_LIBRARY_RELEASE})
    target_link_libraries(${_target} ${SFML_NETWORK_LIBRARY_RELEASE})

    vrm_cmake_add_unit_test(${_target} ${CMAKE_CURRENT_BINARY_DIR}/${_target})
endforeach()

# TODO: rewrite
# TODO: add tests