
#ifndef __EngineX__Sprite__
#define __EngineX__Sprite__

#include "Window.h"

namespace enginex {
    class Sprite {
    public:
        Sprite(std::string, int, int);
        void SetWindow(Window*);
        ~Sprite();
    private:
        Window* enginex_window;
        SDL_Texture* texture;
    };
}

#endif
