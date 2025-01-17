#pragma once

#include <unordered_map>
#include <ranges>
#include <iostream>
#include <SDL2/SDL.h>

#include "Event.h"

namespace tlr
{

class InputManager
{
public:
    static InputManager& GetInstance();

    template<typename KeyType>
    using ModEventMap = std::unordered_map<KeyType, std::unordered_map<Uint16, Event<>>>;

    ModEventMap<SDL_Keycode> KeyPressed;
    ModEventMap<SDL_Keycode> KeyReleased;

    ModEventMap<Uint8> MousePressed;
    ModEventMap<Uint8> MouseReleased;

    ModEventMap<SDL_Keycode> KeyHold;
    ModEventMap<Uint8> MouseHold;

    Event<int, int> MouseMotion;
    Event<int> MouseWheel;

    void Update();
    
private:
    SDL_Keymod _modState;

    InputManager() = default;
    ~InputManager() = default;

    void ProcessEvent(SDL_Event const& event);

    template<typename KeyType>
    void NotifyCallbacks(ModEventMap<KeyType> const& map, KeyType const& key);
};

} // namespace tlr
