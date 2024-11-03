file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(two_views ${SOURCES})

target_link_libraries(two_views PRIVATE entix)