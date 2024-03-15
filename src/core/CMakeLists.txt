file(GLOB_RECURSE TARTAR_ORIGINS_CORE_SRC_FILES *.c)

include_directories("./")

include_directories("../../3dparty/tinycthread/source")

add_library(TOCore STATIC ${TARTAR_ORIGINS_CORE_SRC_FILES})