# Locate GLM library
# This module defines
# GLM_LIBRARY, the name of the library to link against
# GLM_FOUND, if false, do not try to link to GLIB
# GLM_INCLUDE_DIR, where to find glm.hpp
#

SET(GLM_FOUND "NO")

FIND_PATH(GLM_INCLUDE_DIR
  NAMES
  glm/glm.hpp
  HINTS
  $ENV{GLM_ROOT}
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include
  /usr/include
  /opt/local/include
  /opt/include
  PATH_SUFFIXES
  glm-0.9.4.4
)

#message("GLM_INCLUDE_DIR is ${GLM_INCLUDE_DIR}")

SET(GLM_LIBRARY "")

#message("GLM_LIBRARY is ${GLM_LIBRARY}")

SET(GLM_FOUND "YES")