cmake_minimum_required(VERSION 3.24)
project(z5 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON) # pri kompilacii sa povolia aj rozsirenia GNU - kvoli getopt()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(z5 src/z5.c src/monopoly.c)
target_include_directories(z5 PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(z5 m)

