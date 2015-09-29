cmake_minimum_required(VERSION 2.8)
project(SSVStart)
enable_testing()

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/../SSVCMake/cmake/modules/"
    "${CMAKE_SOURCE_DIR}/extlibs/SSVCMake/cmake/modules/")

include(SSVCMake)

SSVCMake_setDefaults()
SSVCMake_findSFML()
SSVCMake_findExtlib(vrm_pp)
SSVCMake_findExtlib(SSVUtils)

SSVCMake_setAndInstallHeaderOnly()

# TODO:
add_custom_target(check 
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Build and then run all the tests and examples.")

add_subdirectory(test)
