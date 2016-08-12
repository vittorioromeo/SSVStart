cmake_minimum_required(VERSION 3.0)

# Include `vrm_cmake`.
list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/../vrm_cmake/cmake/"
    "${CMAKE_SOURCE_DIR}/extlibs/vrm_cmake/cmake/")

include(vrm_cmake)

# Basic project setup.
vrm_cmake_init_project(SSVStart)
vrm_cmake_find_extlib(vrm_pp)
vrm_cmake_find_extlib(SSVUtils)
find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# Alias the include directory.
set(SSVSTART_INC_DIR "${SSVSTART_SOURCE_DIR}/include/")

# Other compiler flags.
vrm_cmake_add_common_compiler_flags()

# The `check` target runs all tests and examples.
vrm_check_target()

# Add subdirectories.
add_subdirectory(test)

# Create header-only install target (automatically glob)
vrm_cmake_header_only_install_glob("${SSVSTART_INC_DIR}" "include")
