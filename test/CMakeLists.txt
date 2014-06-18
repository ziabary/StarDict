cmake_minimum_required(VERSION 2.6.0)

project(test C CXX)

file(GLOB CPP_FILES *.cpp)

include_directories(${StarDict_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} StarDict glib-2.0 z)

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
