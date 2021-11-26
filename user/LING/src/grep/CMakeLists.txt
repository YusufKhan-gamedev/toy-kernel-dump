cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE CXX_SOURCES "main.c")

add_executable(grep ${CXX_SOURCES})

target_include_directories(grep PRIVATE src)
target_link_libraries(grep PRIVATE core system)

target_link_options(grep PRIVATE "-T${CMAKE_SOURCE_DIR}/misc/user.ld")