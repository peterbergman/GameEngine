#include "Window.h"

Window::Window(int height, int width):height(height), width(width){
    InitSDL();
    SetUpWindow();
    SDL_RenderPresent(renderer);
}

void Window::InitSDL() { // TODO: throw error to application
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }
}

void Window::SetUpRenderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

void Window::SetUpWindow() { // TODO: throw error to application
    window = SDL_CreateWindow("Title", 0, 0, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

