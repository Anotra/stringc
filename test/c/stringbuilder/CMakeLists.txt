
project(stringc_stringbuilder)
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE stringc)
add_test(StringBuilder stringc_stringbuilder)