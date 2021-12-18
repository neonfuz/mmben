#include <SDL2/SDL.h>
#include "global.h"
#include "app.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    new_App_options opts = default_new_App_options;
    App app = new_App(opts);
    App_run(&app);
    SDL_Quit();
    return 0;
}
