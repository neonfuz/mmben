#include <SDL2/SDL.h>

#define WIDTH 240
#define HEIGHT 160
#define SCALE 2

typedef struct App {
    SDL_Window *win;
    SDL_Renderer *ren;
    size_t time;
    SDL_bool run;
} App;

App new_App(void) {
    App app = {};
    app.win = SDL_CreateWindow(
        "mmben", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH*SCALE, HEIGHT*SCALE, 0);
    app.ren = SDL_CreateRenderer(app.win, -1, 0);
    SDL_RenderSetLogicalSize(app.ren, WIDTH, HEIGHT);
    SDL_RenderSetIntegerScale(app.ren, 1);
    app.time = 0;
    app.run = 1;
    return app;
}

void App_handle_events(App *app) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT: app->run = 0; break;
        }
    }
}

void App_step(App *app) {
    ++app->time;
}

void App_draw(App *app) {
    SDL_RenderClear(app->ren);
    SDL_RenderPresent(app->ren);
}

void App_run(App *app) {
    while (app->run) {
        App_handle_events(app);
        App_step(app);
        App_draw(app);
    }
}

void App_free(App *app) {
    SDL_DestroyRenderer(app->ren);
    SDL_DestroyWindow(app->win);
}

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    App app = new_App();
    App_run(&app);
    App_free(&app);
    SDL_Quit();
    return 0;
}
