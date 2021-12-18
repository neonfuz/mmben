#include <SDL2/SDL.h>

typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
    void *data;
} App;

App new_App(void);
void App_handle_event(App *app, SDL_Event e);
void App_step(App *app);
void App_draw(App *app);
void App_run(App *app);
void App_run_many(App *apps, int n);
void App_free(App *app);
