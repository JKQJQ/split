cmake_minimum_required(VERSION 2.8)

project(split)
add_compile_options(-std=c++17)
add_definitions(-O2)
find_package(HDF5 COMPONENTS HL REQUIRED)
# set(zstd_INCLUDE_DIRS "/home/team-10/usr/local/include")
# set(zstd_LIBRARIES "/home/team-10/usr/local/lib/libzstd.so")
set(zstd_INCLUDE_DIRS "/home/team-10/zstd/lib")
set(zstd_LIBRARIES "/home/team-10/zstd/lib/libzstd.so")

include_directories(
    ${HDF5_INCLUDE_DIRS}
    ${zstd_INCLUDE_DIRS}
)

add_executable(split split.cpp)
add_executable(merge merge.cpp)
target_link_libraries(split 
    ${HDF5_LIBRARIES}
    ${zstd_LIBRARIES}
)

target_link_libraries(merge 
    ${HDF5_LIBRARIES}
    ${zstd_LIBRARIES}
)

message("${zstd_INCLUDE_DIRS}")