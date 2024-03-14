#include "lib.h"
#include <iostream>
#include "sdl/SDL.h"

namespace lib {
    extern SDL* sdl = nullptr;
    void HelloWorld(){
        std::cout << "Hello World!" << std::endl;
    }

    bool Initialize() {
        sdl = new SDL();
        sdl->Initalize();

        return true;
    }

    void RenderPresent()
    {
        sdl->RenderPresent();
    }

    void GameLoop()
    {
        sdl->GameLoop();
    }

    void Filnalize() {
        sdl->FInalize();
    }
}