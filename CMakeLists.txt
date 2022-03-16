cmake_minimum_required(VERSION 2.8)

project(split)
add_compile_options(-std=c++17)
add_definitions(-O2)
find_package(HDF5 COMPONENTS HL REQUIRED)

include_directories(
    ${HDF5_INCLUDE_DIRS}
)

add_executable(split split.cpp)
add_executable(merge merge.cpp)
target_link_libraries(split 
    ${HDF5_LIBRARIES}
)
