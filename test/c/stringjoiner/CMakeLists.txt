
project(stringc_stringjoiner)
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE stringc)
add_test(StringJoiner stringc_stringjoiner)