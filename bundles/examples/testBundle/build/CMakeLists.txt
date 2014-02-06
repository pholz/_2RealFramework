cmake_minimum_required (VERSION 2.8.11)

project (TestBundle)

set (EXENAME TestBundle)
set (_2REALROOT ../../../..)

if (UNIX)
  add_definitions( -D_UNIX )
  set (EIGEN_INCLUDE_DIRS /usr/include/eigen3)
endif (UNIX)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories (
  ${_2REALROOT}/kernel/src
  ${EIGEN_INCLUDE_DIRS}
)

link_directories (
  ${_2REALROOT}/kernel/lib
)


add_library(${EXENAME} SHARED 
  ../src/MultiplierBlock.cpp
  ../src/ThroughputBlock.cpp
  ../src/TutorialBundle.cpp
)

target_link_libraries (${EXENAME} 
  debug _2RealFrameworkD
  optimized _2RealFramework
)