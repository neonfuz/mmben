#include <SDL2/SDL.h>
#include "global.h"
#include "app.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    App app = new_App();
    App_run(&app);
    SDL_Quit();
    return 0;
}
