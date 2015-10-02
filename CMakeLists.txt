cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/../SSVCMake/cmake/modules/"
    "${CMAKE_SOURCE_DIR}/extlibs/SSVCMake/cmake/modules/")

include(SSVCMake)

# Basic project setup.
vrm_cmake_init_project(SSVStart)
vrm_cmake_find_extlib(vrm_pp)
vrm_cmake_find_extlib(SSVUtils)
SSVCMake_findSFML()

# Alias the include directory.
set(SSVSTART_INC_DIR "${SSVSTART_SOURCE_DIR}/include/")

# Other compiler flags.
vrm_cmake_add_common_compiler_flags()

# Setup user options.
vrm_cmake_add_option_memcheck()
vrm_cmake_add_option_no_exceptions()
vrm_cmake_add_option_werror()

# The `check` target runs all tests and examples.
vrm_check_target()

# Add subdirectories.
add_subdirectory(test)

# Create header-only install target (automatically glob)
vrm_cmake_header_only_install_glob("${SSVSTART_INC_DIR}" "include")