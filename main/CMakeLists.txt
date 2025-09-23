project(Chlorine)

file(GLOB_RECURSE files *.hpp *.cpp)

add_library(Chlorine SHARED ${files})
target_include_directories(Chlorine PUBLIC .)