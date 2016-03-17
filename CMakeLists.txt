cmake_minimum_required(VERSION 3.0)
project(saxpy)

include_directories("${CMAKE_SOURCE_DIR}")

find_package(Armadillo)
if (ARMADILLO_FOUND)
  include_directories("${ARMADILLO_INCLUDE_DIRS}")
endif (ARMADILLO_FOUND)

add_executable(cpp_serial
  cpp_serial.cpp
  printing.cpp
  )

if (ARMADILLO_FOUND)
  add_executable(cpp_arma
    cpp_arma.cpp
    printing.cpp
    )
endif (ARMADILLO_FOUND)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -openmp")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # should check for Clang >= 3.7 here
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp=libomp")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
  message(SEND_ERROR "Unrecognized CXX compiler: ${CXX_COMPILER_NAME}")
endif()
