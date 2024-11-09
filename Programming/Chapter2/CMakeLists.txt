cmake_minimum_required(VERSION 3.10)
project(Project2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

set(CMAKE_BUILD_TYPE Debug)

file(GLOB LIB_SOURCES "lib/*.cpp")

add_library(slib STATIC ${LIB_SOURCES})

target_include_directories(slib PUBLIC lib)

add_executable(B src/B.cpp)
add_executable(C src/C.cpp)
add_executable(D src/D.cpp)
add_executable(E src/E.cpp)
add_executable(F src/F.cpp)

add_executable(t src/test.cpp)

target_link_libraries(B PRIVATE slib)
target_link_libraries(C PRIVATE slib)
target_link_libraries(D PRIVATE slib)
target_link_libraries(E PRIVATE slib)
target_link_libraries(F PRIVATE slib)
target_link_libraries(t PRIVATE slib)

set_target_properties(B C D E F t PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
