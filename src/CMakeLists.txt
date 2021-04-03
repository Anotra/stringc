list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/string.c
    ${CMAKE_CURRENT_LIST_DIR}/stringbuilder.c
    ${CMAKE_CURRENT_LIST_DIR}/stringjoiner.c

    ${CMAKE_CURRENT_LIST_DIR}/charset/utf8.c

    ${CMAKE_CURRENT_LIST_DIR}/encoding/base64.c
)

target_sources(stringc PRIVATE ${SOURCES})
target_sources(stringc_static PRIVATE ${SOURCES})