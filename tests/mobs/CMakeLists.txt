file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(mobs ${SOURCES})

target_link_libraries(mobs PRIVATE entix)