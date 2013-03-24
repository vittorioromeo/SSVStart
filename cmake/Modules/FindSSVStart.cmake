# -*- cmake -*-

# - Find SSVStart
# Find the SSVStart includes and library
# This module defines
# SSVSTART_INCLUDE_DIR, where to find SSVStart headers.
# SSVSTART_LIBRARIES, the libraries needed to use SSVStart.
# SSVSTART_FOUND, If false, do not try to use SSVStart.
# also defined, but not for general use are
# SSVSTART_LIBRARY, where to find the SSVStart library.

FIND_PATH(SSVSTART_INCLUDE_DIR
  NAMES SSVStart/SSVStart.h
  PATH_SUFFIXES include
  PATHS "${PROJECT_SOURCE_DIR}/extlibs/SSVStart/"
  ${SSVSTART_ROOT}
  $ENV{SSVSTART_ROOT}
  /usr/local/
  /usr/
  /sw/         # Fink
  /opt/local/  # DarwinPorts
  /opt/csw/    # Blastwave
  /opt/
)

message("\nFound SSVStart include at: ${SSVSTART_INCLUDE_DIR}.\n")

FIND_LIBRARY(SSVSTART_LIBRARY
  NAMES SSVStart libSSVStart SSVStart-s libSSVStart-s ssvstart libssvstart ssvstart-s libssvstart-s
  PATH_SUFFIXES lib/ lib64/
  PATHS "${PROJECT_SOURCE_DIR}/extlibs/SSVStart/"
  ${SSVSTART_ROOT}
  $ENV{SSVSTART_ROOT}
  /usr/local/
  /usr/
  /sw/         # Fink
  /opt/local/  # DarwinPorts
  /opt/csw/    # Blastwave
  /opt/
)

message("\nFound SSVStart library at: ${SSVSTART_LIBRARY}.\n")

IF (SSVSTART_LIBRARY AND SSVSTART_INCLUDE_DIR)
    SET(SSVSTART_LIBRARIES ${SSVSTART_LIBRARY})
    SET(SSVSTART_FOUND TRUE)
ELSE (SSVSTART_LIBRARY AND SSVSTART_INCLUDE_DIR)
    SET(SSVSTART_FOUND FALSE)
ENDIF (SSVSTART_LIBRARY AND SSVSTART_INCLUDE_DIR)

IF (SSVSTART_FOUND)
    MESSAGE(STATUS "Found SSVStart in ${SSVSTART_INCLUDE_DIR}")
ELSE (SSVSTART_FOUND)
   IF (SSVSTART_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find SSVStart library")
   ENDIF (SSVSTART_FIND_REQUIRED)
ENDIF (SSVSTART_FOUND)

MARK_AS_ADVANCED(
  SSVSTART_LIBRARY
  SSVSTART_INCLUDE_DIR
)
