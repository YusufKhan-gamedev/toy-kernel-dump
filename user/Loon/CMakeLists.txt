cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE CXX_SOURCES "src/*.c")

add_executable(Loon ${CXX_SOURCES})

target_include_directories(Loon PRIVATE src)
target_link_libraries(Loon PRIVATE core system)

target_link_options(Loon PRIVATE "-T${CMAKE_SOURCE_DIR}/misc/user.ld")
