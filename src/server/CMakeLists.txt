file(GLOB_RECURSE TARTAR_ORIGINS_SERVER_SRC_FILES *.c)

include_directories("./")
include_directories("../core")

include_directories("../../3dparty/tinycthread/source")

add_executable(TOServer ${TARTAR_ORIGINS_SERVER_SRC_FILES})
# target_link_libraries(TOServer ws2_32)
target_link_libraries(TOServer TOCore)
