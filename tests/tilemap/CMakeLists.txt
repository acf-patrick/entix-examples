file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(tilemap ${SOURCES})

target_link_libraries(tilemap PRIVATE entix)