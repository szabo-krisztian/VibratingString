add_library(InputManager InputManager.cpp)
target_link_libraries(InputManager PUBLIC $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)