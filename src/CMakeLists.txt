cmake_minimum_required(VERSION 2.6.0)

project(StarDict)

file(GLOB_RECURSE CPP_FILES "*.cpp" )

add_library(${PROJECT_NAME} SHARED ${CPP_FILES} ${INCPP_FILES})

target_link_libraries(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES  VERSION 2.0.0  SOVERSION 2)

include_directories(${PROJECT_SOURCE_DIR}/lib${PROJECT_NAME})
SET(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/lib${PROJECT_NAME}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES lib${PROJECT_NAME}/cls${PROJECT_NAME}.h DESTINATION include/lib${PROJECT_NAME})

###########################################################################
FIND_PACKAGE(glib-2.0)
IF (glib-2.0_FOUND)
    INCLUDE_DIRECTORIES(${glib-2.0_INCLUDE_DIR})
ENDIF()

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG glib-2.0)

if (GLIB_PKG_FOUND)
  message(Found glib-2.0)
  include_directories(${GLIB_PKG_INCLUDE_DIRS})
endif()

find_path(GLIB_INCLUDE_DIR NAMES glib.h PATH_SUFFIXES glib-2.0)
