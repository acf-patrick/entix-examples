file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(switch_scene ${SOURCES})

target_link_libraries(switch_scene PRIVATE entix)