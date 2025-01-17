#include <iostream>
#include <chrono>
#include <cmath>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "InputManager.h"
#include "Approximator.h"

static constexpr int   WINDOW_WIDTH = 640;
static constexpr int   WINDOW_HEIGHT = 480;
static constexpr int   CHORD_RESOLUTION = 50;
static constexpr float SUB_CHORD_LENGTH = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(CHORD_RESOLUTION);
static constexpr int   ANIMATION_SPEED = 75;
static constexpr float HEIGHT_MODIFYING_SPEED = 10.0f;
static constexpr int   APPROXIMATION = 10;

static tlr::Approximator approximator(static_cast<float>(WINDOW_WIDTH), 600.0f); 

bool is_app_running = true;
void Close() { is_app_running = false; }

auto prev_time = std::chrono::steady_clock::now();
bool is_chord_moving = false;
void UserStartedPinching()
{
    approximator.SetHeight(0.0f);
    is_chord_moving = false;
}

void UserFinishedPinching()
{
    prev_time = std::chrono::steady_clock::now();
    is_chord_moving = true;
}

void Pinching(int direction)
{
    if (is_chord_moving) { return; }
    approximator.SetHeight(approximator.GetHeight() + HEIGHT_MODIFYING_SPEED * direction);
}

void DrawChord(SDL_Renderer *renderer)
{
    std::chrono::duration<float> elapsed_duration = std::chrono::steady_clock::now() - prev_time;
    float elapsed_time = ANIMATION_SPEED * elapsed_duration.count();
    float Q = approximator.GetQ();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    std::cout << elapsed_time << std::endl;

    if (!is_chord_moving)
    {
        for (int i = 1; i <= CHORD_RESOLUTION; ++i)
        {
            float x0 = (i - 1) * SUB_CHORD_LENGTH;
            float y0 = WINDOW_HEIGHT / 2 - Q * x0 + (Q / approximator.LENGTH) * static_cast<float>(std::pow(x0, 2));

            float x1 = i * SUB_CHORD_LENGTH;
            float y1 = WINDOW_HEIGHT / 2 - Q * x1 + (Q / approximator.LENGTH) * static_cast<float>(std::pow(x1, 2));

            SDL_RenderDrawLine(renderer, 
                static_cast<int>(x0), static_cast<int>(y0), 
                static_cast<int>(x1), static_cast<int>(y1));
        }
        SDL_RenderPresent(renderer);
        return;
    }

    for (int i = 1; i <= CHORD_RESOLUTION; ++i)
    {
        float x0 = (i - 1) * SUB_CHORD_LENGTH;
        float y0 = WINDOW_HEIGHT / 2.0f - approximator.GetApproximation(x0, elapsed_time, APPROXIMATION);

        float x1 = i * SUB_CHORD_LENGTH;
        float y1 = WINDOW_HEIGHT / 2.0f - approximator.GetApproximation(x1, elapsed_time, APPROXIMATION);

        SDL_RenderDrawLine(renderer, 
            static_cast<int>(x0), static_cast<int>(y0), 
            static_cast<int>(x1), static_cast<int>(y1));
    }
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Vibrating String", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    tlr::InputManager &manager = tlr::InputManager::GetInstance();
    manager.KeyPressed[SDLK_ESCAPE][KMOD_NONE].RegisterCallback(Close);
    manager.MousePressed[SDL_BUTTON_RIGHT][KMOD_NONE].RegisterCallback(UserStartedPinching);
    manager.MouseReleased[SDL_BUTTON_RIGHT][KMOD_NONE].RegisterCallback(UserFinishedPinching);
    manager.MouseWheel.RegisterCallback(Pinching);

    while (is_app_running)
    {
        manager.Update();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        DrawChord(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}