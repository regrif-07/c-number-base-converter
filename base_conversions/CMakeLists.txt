add_library(base_conversions STATIC src/base_conversions.c)

target_include_directories(base_conversions PUBLIC include)

target_link_libraries(base_conversions
        m
        utility)

