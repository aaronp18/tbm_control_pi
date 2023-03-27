cmake_minimum_required(VERSION 3.10)
project(TBMControl VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-DCUSTOM")




# FIND_PACKAGE( OpenCV REQUIRED )   
# include_directories( ${OpenCV_INCLUDE_DIRS} )  

include_directories(TBMControl PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
 )


add_executable(TBMControl
  ${CMAKE_SOURCE_DIR}/src/TBMControlPi.cpp
  ${CMAKE_SOURCE_DIR}/src/EasyCAT.cpp
  ${CMAKE_SOURCE_DIR}/src/Adafruit_ADS1015.cpp
)

# target_link_libraries( TBMControl ${OpenCV_LIBS} )
target_link_libraries( TBMControl bcm2835 wiringPi paho-mqttpp3 paho-mqtt3as )