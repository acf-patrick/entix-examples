file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(animation ${SOURCES})

target_link_libraries(animation PRIVATE entix)