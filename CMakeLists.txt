cmake_minimum_required(VERSION 3.30)
project(NumberBaseConverter C)

set(CMAKE_C_STANDARD 23)

enable_testing()

include(FetchContent)

FetchContent_Declare(
        Unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
)
FetchContent_MakeAvailable(Unity)

add_subdirectory(utility)
add_subdirectory(base_conversions)
add_subdirectory(NumberBaseConverter)

add_subdirectory(tests)