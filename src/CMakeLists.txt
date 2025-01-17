cmake_minimum_required(VERSION 3.10)
project(Vibrating_String_Project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 CONFIG REQUIRED)

add_executable(Main main.cpp)
add_subdirectory(input-manager)
add_subdirectory(approximator)

target_include_directories(Main
    PRIVATE
    input-manager
    approximator
)

target_link_libraries(Main
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>       
    InputManager
    Approximator
)