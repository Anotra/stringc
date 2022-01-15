cmake_minimum_required(VERSION 3.13)

enable_language(C)
set(CMAKE_C_STANDARD 99)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (WIN32)
    set(WINDOWS_EXPORT_ALL_SYMBOLS 1)
endif()

if (CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic")
    set(CMAKE_C_FLAGS_DEBUG "-g")
    set(CMAKE_C_FLAGS_RELEASE "-O3")
endif()

include(CheckLanguage)
check_language(CXX)
if (CMAKE_CXX_COMPILER)
    enable_language(CXX)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
        set(CMAKE_CXX_FLAGS_DEBUG "-g")
        set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    endif()
endif()

option(BUILD_TESTS "Build Test Files" ON)

project(stringc)
add_library(${PROJECT_NAME} SHARED)
target_include_directories(${PROJECT_NAME} PUBLIC include)

project(stringc_static)
add_library(${PROJECT_NAME} STATIC)
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(src)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

install(TARGETS stringc LIBRARY DESTINATION lib)
install(TARGETS stringc_static LIBRARY DESTINATION lib)
file(GLOB STRINGC_PUBLIC_INCLUDE_FILES include/stringc/*.h)
install(FILES ${STRINGC_PUBLIC_INCLUDE_FILES} DESTINATION include/stringc)
