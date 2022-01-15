list(APPEND SOURCES
    string.c
    stringbuilder.c
    stringjoiner.c

    charset/utf8.c

    encoding/base64.c
)


target_sources(stringc PRIVATE ${SOURCES})
target_sources(stringc_static PRIVATE ${SOURCES})