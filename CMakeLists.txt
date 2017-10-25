# Specify the minimum version for CMake

cmake_minimum_required(VERSION 3.4.1)

add_compile_options(-std=c++14)

project (Contrast_enhancement VERSION 0.1 LANGUAGES CXX)
#Bring the headers into the project
include_directories(include)
 
#Bring sources into the project:
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h" "include/*.hpp")

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

find_package( OpenCV REQUIRED )
add_executable(Contrast_enhancement ${SOURCES} ${HEADERS})
target_link_libraries( Contrast_enhancement ${OpenCV_LIBS} )
