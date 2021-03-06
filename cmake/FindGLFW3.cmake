set( _glfw3_HEADER_SEARCH_DIRS
"/usr/include"
"/usr/local/include"
"${CMAKE_SOURCE_DIR}/includes"
"C:/Program Files (x86)/glfw/include" )
set( _glfw3_LIB_SEARCH_DIRS
"/usr/lib"
"/usr/local/lib"
"${CMAKE_SOURCE_DIR}/lib"
"C:/Program Files (x86)/glfw/lib-msvc110" )

# Check environment for root search directory
set( _glfw3_ENV_ROOT $ENV{glfw3_ROOT} )
if( NOT glfw3_ROOT AND _glfw3_ENV_ROOT )
	set(glfw3_ROOT ${_glfw3_ENV_ROOT} )
endif()

# Put user specified location at beginning of search
if( glfw3_ROOT )
	list( INSERT _glfw3_HEADER_SEARCH_DIRS 0 "${glfw3_ROOT}/include" )
	list( INSERT _glfw3_LIB_SEARCH_DIRS 0 "${glfw3_ROOT}/lib" )
endif()

# Search for the header
FIND_PATH(glfw3_INCLUDE_DIR "glfw/glfw3.h"
PATHS ${_glfw3_HEADER_SEARCH_DIRS} )

# Search for the library
FIND_LIBRARY(glfw3_LIBRARY NAMES glfw3 glfw
PATHS ${_glfw3_LIB_SEARCH_DIRS} )
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(glfw3 DEFAULT_MSG
glfw3_LIBRARY glfw3_INCLUDE_DIR)