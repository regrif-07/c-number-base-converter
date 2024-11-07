cmake_minimum_required(VERSION 3.30)
project(NumberBaseConverter C)

set(CMAKE_C_STANDARD 23)

include_directories(include)

add_executable(NumberBaseConverter src/main.c
        src/base_conversions.c
        include/base_conversions.h
        src/string_utility.c
        include/string_utility.h
        src/numbers_utility.c
        include/numbers_utility.h)

target_link_libraries(NumberBaseConverter m)