file(GLOB_RECURSE TARTAR_ORIGINS_CLIENT_SRC_FILES *.c)

include_directories("./")
include_directories("../core")
include_directories("../../3dparty/tinycthread/source")

add_executable(TOClient ${TARTAR_ORIGINS_CLIENT_SRC_FILES})
# target_link_libraries(TOClient ws2_32)
target_link_libraries(TOClient TOCore)
