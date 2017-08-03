project("dubboc")
cmake_minimum_required(VERSION 2.8)

add_compile_options(-std=c++1y)
add_compile_options(-fPIC)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

# When installing Folly & Wangle in a non-default prefix, this will let
# projects linking against libwangle.so to find libfolly.so automatically.
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Folly REQUIRED)
find_package(Wangle REQUIRED)

aux_source_directory(. DIR_SRCS)

set(DUBBOC_HEADER_DIRS
        src/cluster
        src/common
        src/config
        src/container
        src/filter
        src/monitor
        src/registry
        src/remoting
        src/rpc
        )

foreach(dir ${DUBBOC_HEADER_DIRS})
    file(GLOB_RECURSE headers ${dir}/*.h)
    set(DUBBOC_HEADERS
            ${DUBBOC_HEADERS}
            ${headers})
endforeach()


FILE(GLOB_RECURSE DUBBOC_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*.c*")
#set(DUBBOC_SOURCES ${PROJECT_SOURCE_DIR}/src/*.c*)


add_library(dubboc ${DUBBOC_HEADER_DIRS} ${DUBBOC_SOURCES})