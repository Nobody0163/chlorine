project(ChlorineTesting)

file(GLOB_RECURSE files ./*.hpp ./*.cpp)

add_executable(ChlorineTesting ${files})
target_link_libraries(ChlorineTesting Chlorine)