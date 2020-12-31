cmake_minimum_required(VERSION 3.10)

project(stringc)
add_library(${PROJECT_NAME} SHARED
    src/string.c
    src/stringbuilder.c
    src/stringjoiner.c
)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src/include)

project(test_stringc)
add_executable(${PROJECT_NAME}
    test/test.c
)
target_link_libraries(${PROJECT_NAME} PRIVATE stringc)