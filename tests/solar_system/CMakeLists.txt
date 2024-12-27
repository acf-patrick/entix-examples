file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(solar_system ${SOURCES})

target_link_libraries(solar_system PRIVATE entix)