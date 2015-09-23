# Locate MCPP library
# This module defines
# MCPP_LIBRARY, the name of the library to link against
# MCPP_FOUND, if false, do not try to link to MCPP
# MCPP_INCLUDE_DIR, where to find mcpp_lib.h
#

SET(MCPP_FOUND "NO")

FIND_PATH(MCPP_INCLUDE_DIR
  NAMES
  mcpp_lib.h
  HINTS
  $ENV{MCPP_ROOT}
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include
  /usr/include
  /opt/local/include
  /opt/include
  PATH_SUFFIXES
  src
)

#message("MCPP_INCLUDE_DIR is ${MCPP_INCLUDE_DIR}")

FIND_LIBRARY(MCPP_LIBRARY
  NAMES
  mcpp
  HINTS
  $ENV{MCPP_ROOT}
  PATH_SUFFIXES lib64 lib bin
  PATHS
  /usr/local
  /usr
  /opt/local
  /opt
)

#message("MCPP_LIBRARY is ${MCPP_LIBRARY}")

SET(MCPP_FOUND "YES")