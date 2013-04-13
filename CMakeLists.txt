cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type.")
project(SSVStart)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -W -pedantic" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-fno-omit-frame-pointer -g3 -gdwarf-2 -O3" CACHE STRING "" FORCE)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../SSVUtils/cmake/Modules/;${CMAKE_MODULE_PATH}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extlibs/SSVUtils/cmake/Modules/;${CMAKE_MODULE_PATH}")
set(SSVSTART_BUILD_SHARED_LIB FALSE CACHE BOOL "Build shared libraries.")

if(SSVSTART_BUILD_SHARED_LIB)
	set(LIB_TYPE SHARED)
else()
	set(LIB_TYPE STATIC)
endif()

set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Look for static SFML libraries.")
find_package(SFML 2 COMPONENTS audio graphics window system network)
if(NOT SFML_FOUND)
	set(SFML_INCLUDE_DIR "" CACHE STRING "SFML2 include directory")
	set(SFML_SYSTEM_LIBRARY "" CACHE STRING "SFML2 System library file")
	set(SFML_WINDOW_LIBRARY "" CACHE STRING "SFML2 Window library file")
	set(SFML_GRAPHICS_LIBRARY "" CACHE STRING "SFML2 Graphics library file")
	set(SFML_NETWORK_LIBRARY "" CACHE STRING "SFML2 Network library file")
	set(SFML_AUDIO_LIBRARY "" CACHE STRING "SFML2 Audio library file")
	message("\n-> SFML directory not found. Set include and libraries manually.")
endif()

find_package(SSVUtils REQUIRED)

set(SRC_DIR "src")
set(INC_DIR "include")

file(GLOB SRC_LIST
	"${INC_DIR}/${PROJECT_NAME}/*.h"
	"${SRC_DIR}/${PROJECT_NAME}/*.cpp"
	"${INC_DIR}/${PROJECT_NAME}/Assets/*.h"
	"${SRC_DIR}/${PROJECT_NAME}/Assets/*.cpp"
	"${INC_DIR}/${PROJECT_NAME}/Camera/*.h"
	"${SRC_DIR}/${PROJECT_NAME}/Camera/*.cpp"
	"${INC_DIR}/${PROJECT_NAME}/GameSystem/*.h"
	"${SRC_DIR}/${PROJECT_NAME}/GameSystem/*.cpp"
	"${INC_DIR}/${PROJECT_NAME}/GameSystem/Timers/*.h"
	"${SRC_DIR}/${PROJECT_NAME}/GameSystem/Timers/*.cpp"
	"${INC_DIR}/${PROJECT_NAME}/Input/*.h"
	"${SRC_DIR}/${PROJECT_NAME}/Input/*.cpp"
	"${INC_DIR}/${PROJECT_NAME}/Tileset/*.h"
	"${SRC_DIR}/${PROJECT_NAME}/Tileset/*.cpp"
	"${INC_DIR}/${PROJECT_NAME}/Utils/*.h"
	"${SRC_DIR}/${PROJECT_NAME}/Utils/*.cpp"
)

include_directories(${INC_DIR})
include_directories(${SFML_INCLUDE_DIR})
include_directories(${SSVUTILS_INCLUDE_DIR})

add_library(${PROJECT_NAME} ${LIB_TYPE} ${SRC_LIST})
target_link_libraries(SSVStart ${SFML_AUDIO_LIBRARY})
target_link_libraries(SSVStart ${SFML_GRAPHICS_LIBRARY})
target_link_libraries(SSVStart ${SFML_WINDOW_LIBRARY})
target_link_libraries(SSVStart ${SFML_SYSTEM_LIBRARY})
target_link_libraries(SSVStart ${SFML_NETWORK_LIBRARY})
target_link_libraries(SSVStart ${SSVUTILS_LIBRARY})

if(SSVSTART_BUILD_SHARED_LIB)
	set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)
else()
	set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -s-d)
	set_target_properties(${PROJECT_NAME} PROPERTIES RELEASE_POSTFIX -s)
endif()

if(WIN32)
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
else()
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION lib LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
endif()

install(DIRECTORY ${INC_DIR} DESTINATION .)
