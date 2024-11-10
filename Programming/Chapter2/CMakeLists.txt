cmake_minimum_required(VERSION 3.10)
project(Programming_2)

file(GLOB LIB_SOURCES "lib/*.cpp")
add_library(_ STATIC ${LIB_SOURCES})

file(GLOB SOURCES "src/*.cpp")
foreach(SOURCE ${SOURCES})
    get_filename_component(foo ${SOURCE} NAME_WE)
    add_executable(${foo} ${SOURCE})
    target_link_libraries(${foo} PRIVATE _)
endforeach()