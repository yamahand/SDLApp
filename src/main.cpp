#include "stdafx.h"
#include <stdio.h>
#include <cstdlib>
#include "lib.h"

//#define SDL_MAIN_USE_CALLBACKS
//#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]){
    lib::HelloWorld();
	lib::Initialize();

    lib::GameLoop();

    lib::Filnalize();

    return 0;
}