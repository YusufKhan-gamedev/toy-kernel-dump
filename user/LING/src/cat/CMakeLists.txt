cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE CXX_SOURCES "main.c")

add_executable(cat ${CXX_SOURCES})

target_include_directories(cat PRIVATE src)
target_link_libraries(cat PRIVATE core system)

target_link_options(cat PRIVATE "-T${CMAKE_SOURCE_DIR}/misc/user.ld")