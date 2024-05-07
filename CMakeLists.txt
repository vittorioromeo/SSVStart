cmake_minimum_required(VERSION 3.0)

# -----------------------------------------------------------------------------
# CPM
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
set(CPM_DOWNLOAD_VERSION 0.25.1)

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION} AND CPM_VERSION STREQUAL CPM_DOWNLOAD_VERSION))
  message(STATUS "Downloading CPM.cmake")
  file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})
# -----------------------------------------------------------------------------

CPMAddPackage(
  NAME SFML
  GITHUB_REPOSITORY vittorioromeo/SFML
  GIT_TAG 06b4c6ceaabaa3e15e88ca70cf61ae7bba69ad39
)

# Include `vrm_cmake`.
list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake/"
    "${CMAKE_SOURCE_DIR}/cmake/modules/"
    "${CMAKE_SOURCE_DIR}/../vrm_cmake/cmake/"
    "${CMAKE_SOURCE_DIR}/extlibs/vrm_cmake/cmake/")

include(vrm_cmake)

# Basic project setup.
vrm_cmake_set_cxxstd(20)

project(SSVStart CXX)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

vrm_cmake_init_project_name_upper()
vrm_cmake_init_project_source_dir()
vrm_cmake_init_project_common_module_paths()

vrm_cmake_message("initialized project ${project_name}")

vrm_cmake_find_extlib(vrm_pp)
vrm_cmake_find_extlib(SSVUtils)
#find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)
include_directories(${SFML_SOURCE_DIR}/include)

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
