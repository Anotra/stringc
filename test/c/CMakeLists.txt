project(stringc_mainc)
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE stringc)


project(stringc_test_stringbuilder)
add_executable(${PROJECT_NAME} stringbuilder.c)
target_link_libraries(${PROJECT_NAME} PRIVATE stringc)
add_test(stringbuilder ${PROJECT_NAME})

project(stringc_test_stringjoiner)
add_executable(${PROJECT_NAME} stringjoiner.c)
target_link_libraries(${PROJECT_NAME} PRIVATE stringc)
add_test(stringjoiner ${PROJECT_NAME})

project(stringc_test_base64)
add_executable(${PROJECT_NAME} base64.c)
target_link_libraries(${PROJECT_NAME} PRIVATE stringc)
add_test(base64 ${PROJECT_NAME})


project(stringc_test_utf8)
add_executable(${PROJECT_NAME} utf8.c)
target_link_libraries(${PROJECT_NAME} PRIVATE stringc)
add_test(utf8 ${PROJECT_NAME})