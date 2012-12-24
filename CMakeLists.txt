# Requires at least CMake 2.6 to configure the package.
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CXX_DISABLE_WERROR TRUE)
INCLUDE(cmake/base.cmake)
INCLUDE(cmake/boost.cmake)

SET(PROJECT_NAME kite-fcl-bridge)
SET(PROJECT_DESCRIPTION
  "Utility package for computing best fit fcl over a polygon soup.")
SET(PROJECT_URL "")

# Where to compile shared objects
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

SET(${PROJECT_NAME}_HEADERS
  include/kite-fcl-bridge/fwd.hh
  include/kite-fcl-bridge/macros.hh
  include/kite-fcl-bridge/types.hh
  include/kite-fcl-bridge/util.hh
  include/kite-fcl-bridge/body.hh
  include/kite-fcl-bridge/body-factory.hh
  include/kite-fcl-bridge/polyhedron.hh
  )

SETUP_PROJECT()

# Declare dependencies
SEARCH_FOR_BOOST()
ADD_REQUIRED_DEPENDENCY("KineoController")
ADD_REQUIRED_DEPENDENCY("fcl")

PKG_CONFIG_APPEND_LIBS(${PROJECT_NAME})

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)

SETUP_PROJECT_FINALIZE()
