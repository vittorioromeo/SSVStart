cmake_minimum_required(VERSION 2.8)
project(SSVStart)

set(SSVSTART_BUILD_SHARED_LIB FALSE CACHE BOOL "Build shared libraries.")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type." FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" CACHE STRING "" FORCE)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extlibs/SSVUtils/cmake/Modules/;${CMAKE_MODULE_PATH}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -pg -Og" CACHE STRING "" FORCE)

set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Look for static SFML libraries.")

find_package(SFML 2 COMPONENTS audio graphics window system network)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	message("\nSFML found and included\n")
else()
	set(SFML_INCLUDE_DIR "" CACHE STRING "SFML2 include directory")
	set(SFML_SYSTEM_LIBRARY "" CACHE STRING "SFML2 System library file")
	set(SFML_WINDOW_LIBRARY "" CACHE STRING "SFML2 Window library file")
	set(SFML_GRAPHICS_LIBRARY "" CACHE STRING "SFML2 Graphics library file")
	set(SFML_NETWORK_LIBRARY "" CACHE STRING "SFML2 Network library file")
	set(SFML_AUDIO_LIBRARY "" CACHE STRING "SFML2 Audio library file")
	message("\n-> SFML directory not found. Set include and libraries manually.")
endif()

find_package(SSVUtils REQUIRED)
if(SSVUTILS_FOUND)
	include_directories(${SSVUTILS_INCLUDE_DIR})
	message("\nSSVUtils found and included\n")
else()
	set(SSVUTILS_ROOT "" CACHE PATH "SSVUtils top-level directory")
	message("\n-> SSVUtils directory not found. Set SSVUTILS_ROOT to SSVUtils' top-level path (containing both \"include\" and \"lib\" directories).")
endif()

if(SSVSTART_BUILD_SHARED_LIB)
	set(LIB_TYPE SHARED)
else()
	set(LIB_TYPE STATIC)
endif()

set(SRC_DIR "src")
set(INC_DIR "include")

set(
	SOURCES
	${INC_DIR}/${PROJECT_NAME}/Assets/AssetFolder.h
	${INC_DIR}/${PROJECT_NAME}/Assets/AssetManager.h
	${INC_DIR}/${PROJECT_NAME}/Camera/Camera.h
	${INC_DIR}/${PROJECT_NAME}/GameSystem/GameState.h
	${INC_DIR}/${PROJECT_NAME}/GameSystem/GameWindow.h
	${INC_DIR}/${PROJECT_NAME}/GameSystem/Timers.h
	${INC_DIR}/${PROJECT_NAME}/Input/Combo.h
	${INC_DIR}/${PROJECT_NAME}/Input/Manager.h
	${INC_DIR}/${PROJECT_NAME}/Input/Trigger.h
	${INC_DIR}/${PROJECT_NAME}/Tileset/Tileset.h
	${INC_DIR}/${PROJECT_NAME}/Utils/ThreadWrapper.h
	${INC_DIR}/${PROJECT_NAME}/Utils/Utils.h
	${SRC_DIR}/${PROJECT_NAME}/Assets/AssetFolder.cpp
	${SRC_DIR}/${PROJECT_NAME}/Assets/AssetManager.cpp
	${SRC_DIR}/${PROJECT_NAME}/Camera/Camera.cpp
	${SRC_DIR}/${PROJECT_NAME}/GameSystem/GameState.cpp
	${SRC_DIR}/${PROJECT_NAME}/GameSystem/GameWindow.cpp
	${SRC_DIR}/${PROJECT_NAME}/GameSystem/GWProperties.cpp
	${SRC_DIR}/${PROJECT_NAME}/Input/Combo.cpp
	${SRC_DIR}/${PROJECT_NAME}/Input/Manager.cpp
	${SRC_DIR}/${PROJECT_NAME}/Input/Trigger.cpp
	${SRC_DIR}/${PROJECT_NAME}/Tileset/Tileset.cpp
	${SRC_DIR}/${PROJECT_NAME}/Utils/Utils.cpp
)

include_directories(${INC_DIR})

add_library(${PROJECT_NAME} ${LIB_TYPE} ${SOURCES})
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
	install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
else()
	install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION lib
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
endif()

install(DIRECTORY ${INC_DIR}
	DESTINATION .)
