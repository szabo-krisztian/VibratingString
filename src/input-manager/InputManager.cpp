#include "InputManager.h"

#include <ranges>

namespace tlr
{

InputManager& InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

void InputManager::Update()
{
    _modState = SDL_GetModState();
    
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ProcessEvent(event);
    }

    Uint8 const* keyboardState = SDL_GetKeyboardState(nullptr);
    for (auto const& key : KeyHold | std::views::keys)
    {
        if (!keyboardState[SDL_GetScancodeFromKey(key)]) continue;

        for (auto const& mod : KeyHold[key] | std::views::keys)
        {
            if ((_modState & (mod)) == mod) KeyHold[key][mod].Raise();
        }   
    }

    int x, y;
    Uint32 mouseState = SDL_GetMouseState(&x, &y);
    for (auto const& button : MouseHold | std::views::keys)
    {
        if (!(mouseState & SDL_BUTTON(button))) continue;

        for (auto const& mod : MouseHold[button] | std::views::keys)
        {
            if ((_modState & (mod)) == mod) MouseHold[button][mod].Raise();
        }
    }

    MouseMotion.Raise(x, y);
}

void InputManager::ProcessEvent(SDL_Event const& event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            NotifyCallbacks(KeyPressed, event.key.keysym.sym);
        } break;

        case SDL_KEYUP:
        {
            NotifyCallbacks(KeyReleased, event.key.keysym.sym);
        } break;

        case SDL_MOUSEBUTTONDOWN:
        {
            NotifyCallbacks(MousePressed, event.button.button);
        } break;

        case SDL_MOUSEBUTTONUP:
        {
            NotifyCallbacks(MouseReleased, event.button.button);
        } break;

        case SDL_MOUSEWHEEL:
        {
            MouseWheel.Raise(event.wheel.y);
        } break;
    }
}

template<typename KeyType>
void InputManager::NotifyCallbacks(ModEventMap<KeyType> const& map, KeyType const& key)
{
    auto it = map.find(key);

    if (it == map.end())
    {
        return;
    }

    for (auto const& mod : it->second | std::views::keys)
    {
        if ((_modState & (mod)) == mod) it->second.at(mod).Raise();
    }
}

} // namespace tlr