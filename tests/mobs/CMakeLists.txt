file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(mobs ${SOURCES})

target_include_directories(mobs PRIVATE
    ${PROJECT_SOURCE_DIR}/external/entix/external/box2d/include
)

target_link_libraries(mobs PRIVATE 
    entix
    box2d
    yaml-cpp
)