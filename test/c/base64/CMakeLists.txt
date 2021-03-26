
project(stringc_base64_test)
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE stringc)
add_test(Base64 stringc_base64_test)