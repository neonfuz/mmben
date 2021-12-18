#include <SDL2/SDL.h>
#include "global.h"

typedef struct App App;
typedef struct Game Game;

struct Game {
    int width, height, scale;
    size_t data_size;
    void (*init)(struct App *a);
    void (*step)(struct App *a);
    void (*draw)(struct App *a);
    void (*free)(struct App *a);
};

struct App {
    SDL_Window *win;
    SDL_Renderer *ren;
    Game game;
    void *data;
};

App new_App(Game g);
void App_handle_event(App *app, SDL_Event e);
void App_step(App *app);
void App_draw(App *app);
void App_run(App *app);
void App_run_many(App *apps, int n);
void App_free(App *app);
int Game_run(Game g);