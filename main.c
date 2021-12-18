#include <SDL2/SDL.h>
#include "global.h"
#include "app.h"

struct Game_data {
    size_t time;
};

void mmben_init(App *app) {
    app->data = calloc(1, sizeof(Game_data));
}

void mmben_step(App *app) {
    ++app->data->time;
}

void mmben_draw(App *app) {
    size_t time = app->data->time;
    if (time % 60 == 0)
        printf("%ld\n", time/60);
}

void mmben_free(App *app) {
    free(app->data);
}

static const
Game mmben = {
    .width = 240, .height = 160, .scale = 2,
    mmben_init, mmben_step, mmben_draw, mmben_free,
};

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    App app = new_App(mmben);
    App_run(&app);
    SDL_Quit();
    return 0;
}
