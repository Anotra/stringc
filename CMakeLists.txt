cmake_minimum_required(VERSION 3.13)

enable_language(C)
set(CMAKE_C_STANDARD 99)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

option(BUILD_TESTS "Build Test Files" ON)

include(GenerateExportHeader)
project(stringc)
add_library(${PROJECT_NAME} SHARED)
target_include_directories(${PROJECT_NAME} PUBLIC include)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/export.h)
set_target_properties(${PROJECT_NAME} PROPERTIES C_VISIBILITY_PRESET internal)

project(stringc_static)
add_library(${PROJECT_NAME} STATIC)
target_compile_options(${PROJECT_NAME} PRIVATE -g -Wall)
target_include_directories(${PROJECT_NAME} PUBLIC include)
set_target_properties(${PROJECT_NAME} PROPERTIES C_VISIBILITY_PRESET internal)

add_subdirectory(src)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

install(TARGETS stringc LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS stringc_static LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include/ DESTINATION include)