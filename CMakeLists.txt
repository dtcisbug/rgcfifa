cmake_minimum_required(VERSION 2.6)

project(rgc CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CXX_FLAGS
 -g3
 -DCHECK_PTHREAD_RETURN_VALUE
 -D_FILE_OFFSET_BITS=64
 -Wall
 -Wextra
 #-Werror
 #-Wconversion
 -Wno-unused-parameter
 #-Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 -std=c++11
 -rdynamic
 -pg
 )
if(CMAKE_BUILD_BITS EQUAL 32)
  list(APPEND CXX_FLAGS "-m32")
endif()
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

FIND_LIBRARY(SCRIPT_LIB libscript.a ./script)
#FIND_LIBRARY(MONO_LIB libmonosgen-2.0.a ./thirdpart)
#FIND_LIBRARY(MONO_LIB libmonoboehm-2.0_p.a ./thirdpart)
FIND_LIBRARY(MONO_LIB libmonoboehm-2.0.a ./thirdpart)

include_directories(${PROJECT_SOURCE_DIR})

string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

add_subdirectory(Common)
#add_subdirectory(script)
add_subdirectory(Network)
add_subdirectory(Server)
#add_subdirectory(Client)

