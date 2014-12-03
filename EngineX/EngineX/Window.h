#ifndef __EngineX__Window__
#define __EngineX__Window__

#include "Engine.h"

namespace enginex {
    class Window {
    public:
        Window(std::string, int, int);
        SDL_Renderer* GetRenderer();
        ~Window();
    private:
        int height, width;
        std::string title;
        SDL_Window* window;
        SDL_Renderer* renderer;
        void InitSDL();
        void SetUpRenderer();
        void SetUpWindow();
    };
}

#endif
