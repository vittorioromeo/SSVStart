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
vrm_cmake_generate_unit_tests(SSVS_TEST_SOURCES)

set(SFML_LIBRARIES sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

foreach(_t IN LISTS vrm_cmake_out)
    target_link_libraries(${_t} ${SFML_LIBRARIES})
endforeach()
