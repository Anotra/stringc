cmake_minimum_required(VERSION 3.10)
include(CheckLanguage)

enable_language(C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS "-Wall -Wextra")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_RELEASE "-O3")
endif()

project(stringc)
add_library(${PROJECT_NAME} SHARED
    src/string.c
    src/stringbuilder.c
    src/stringjoiner.c
    src/charset/utf8.c
    src/encoding/base64.c
)
target_include_directories(${PROJECT_NAME} PUBLIC include)

check_language(CXX)
if (CMAKE_CXX_COMPILER)
    enable_language(CXX)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "-Wall -Wextra")
        set(CMAKE_CXX_FLAGS_DEBUG "-g")
        set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    endif()

    project(test_stringcpp)
    add_executable(${PROJECT_NAME} test/test.cpp)
    target_link_libraries(${PROJECT_NAME} PRIVATE stringc)
endif()

project(test_stringc)
add_executable(${PROJECT_NAME} test/test.c)
target_link_libraries(${PROJECT_NAME} PRIVATE stringc)