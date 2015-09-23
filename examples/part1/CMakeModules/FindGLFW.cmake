# Locate SDL2 library
# This module defines
# SDL2_LIBRARY, the name of the library to link against
# SDL2_FOUND, if false, do not try to link to SDL2
# SDL2_INCLUDE_DIR, where to find SDL2/SDL.h
#

SET(GLFW_FOUND "NO")

FIND_PATH(GLFW_INCLUDE_DIR
  NAMES
  GLFW/glfw3.h
  HINTS
  $ENV{GLFW_ROOT}
  PATH_SUFFIXES
  include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include
  /usr/include
  /opt/local/include
  /opt/include
)

#message("GLFW_INCLUDE_DIR is ${SDL2_INCLUDE_DIR}")

FIND_LIBRARY(GLFW_LIBRARY
  NAMES
  glfw3dll
  HINTS
  $ENV{GLFW_ROOT}
  PATH_SUFFIXES
  lib
  lib64
  bin
  lib/x86
  lib/x64
  lib-vc2013
  lib-vc2012
  lib-vc2010
  PATHS
  /usr/local
  /usr
  /opt/local
  /opt
)

#message("GLFW_LIBRARY is ${GLFW_LIBRARY}")

SET(GLFW_FOUND "YES")