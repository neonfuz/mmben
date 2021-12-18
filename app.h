#include <SDL2/SDL.h>

typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
    size_t time;

} App;

typedef struct {
    int winX, winY;
} new_App_options;

static const new_App_options default_new_App_options = {
    .winX = SDL_WINDOWPOS_CENTERED,
    .winY = SDL_WINDOWPOS_CENTERED,
};

App new_App(new_App_options opts);
void App_handle_event(App *app, SDL_Event e);
void App_step(App *app);
void App_draw(App *app);
void App_run(App *app);
void App_run_many(App *apps, int n);
void App_free(App *app);
