file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(mobs ${SOURCES})

set(USE_PHYSIC_SYSTEM ON CACHE BOOL "Enable physic system")

target_link_libraries(mobs PRIVATE entix)