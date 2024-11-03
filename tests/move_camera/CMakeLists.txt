file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(move_camera ${SOURCES})

target_link_libraries(move_camera PRIVATE entix)