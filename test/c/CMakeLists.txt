project(stringc_test)
add_executable(${PROJECT_NAME} main.c
  base64.c
  utf8.c
  stringbuilder.c
  stringjoiner.c
)
target_link_libraries(${PROJECT_NAME} PRIVATE stringc)

add_test(base64 ${PROJECT_NAME} base64)
add_test(utf8 ${PROJECT_NAME} utf8)
add_test(stringbuilder ${PROJECT_NAME} stringbuilder)
add_test(stringjoiner ${PROJECT_NAME} stringjoiner)