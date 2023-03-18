cmake_minimum_required(VERSION 3.10)
project(TBMControlPi VERSION 1.0)
add_executable(TBMControlPi tbmcontrolpi.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CUSTOM 1)

# FIND_PACKAGE( OpenCV REQUIRED )   
# include_directories( ${OpenCV_INCLUDE_DIRS} )  

include_directories(TBMControlPi PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
 )


add_executable(TBMControlPi
  ${CMAKE_SOURCE_DIR}/src/TBMControlPi.cpp
)

# target_link_libraries( TBMControlPi ${OpenCV_LIBS} )
target_link_libraries( TBMControlPi )