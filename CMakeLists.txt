cmake_minimum_required(VERSION 2.8)
project(SSVStart)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extlibs/SSVCMake/cmake/modules/;${CMAKE_MODULE_PATH}")
include(SSVCMake)

SSVCMake_setDefaults()
SSVCMake_findSFML()
SSVCMake_findExtlib(SSVUtils)

set(SSVSTART_USE_JSON TRUE CACHE BOOL "Use JSON tools/utilities (Requires SSVUtilsJson).")
if(SSVSTART_USE_JSON)
	SSVCMake_findExtlib(SSVUtilsJson)
else()
	add_definitions(-DSSVS_N_USE_JSON)
endif()

SSVCMake_setAndInstallHeaderOnly()
