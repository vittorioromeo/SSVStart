cmake_minimum_required(VERSION 3.0)

# -----------------------------------------------------------------------------
# CPM
include(cmake/CPM.cmake)
# -----------------------------------------------------------------------------

set(BUILD_SHARED_LIBS false)
set(SFML_STATIC_LIBRARIES true)
set(SFML_ENABLE_PCH true)
set(SFML_ENABLE_LIFETIME_TRACKING true)

CPMAddPackage(
  NAME SFML
  GITHUB_REPOSITORY vittorioromeo/SFML
  GIT_TAG cabd5ce12a67c203be092362588c74f6048f72c2
)

set(SFML_ENABLE_LIFETIME_TRACKING true)

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
