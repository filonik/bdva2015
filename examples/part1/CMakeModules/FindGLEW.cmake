# Locate GLEW library
# This module defines
# GLEW_LIBRARY, the name of the library to link against
# GLEW_FOUND, if false, do not try to link to GLEW
# GLEW_INCLUDE_DIR, where to find GL/glew.h
#

SET(GLEW_FOUND "NO")

FIND_PATH(GLEW_INCLUDE_DIR
  NAMES
  GL/glew.h
  HINTS
  $ENV{GLEW_ROOT}
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

#message("GLEW_INCLUDE_DIR is ${GLEW_INCLUDE_DIR}")

FIND_LIBRARY(GLEW_LIBRARY
  NAMES
  glew glew32
  HINTS
  $ENV{GLEW_ROOT}
  PATH_SUFFIXES lib lib64 bin lib/x86 lib/x64 lib/Release/Win32 lib/Release/x64
  PATHS
  /usr/local
  /usr
  /opt/local
  /opt
)

#message("GLEW_LIBRARY is ${GLEW_LIBRARY}")

SET(GLEW_FOUND "YES")