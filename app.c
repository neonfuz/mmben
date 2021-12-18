#include "global.h"
#include "app.h"

void App_handle_event(App *app, SDL_Event e) {
    switch (e.type) {
    case SDL_WINDOWEVENT:
        if (e.window.windowID != SDL_GetWindowID(app->win) ||
            e.window.event != SDL_WINDOWEVENT_CLOSE)
            break;
        // fall through
    case SDL_QUIT:
        SDL_DestroyWindow(app->win);
        app->win = NULL;
        break;
    }
}

void App_step(App *app) {
}

void App_draw(App *app) {
    SDL_RenderClear(app->ren);
    SDL_RenderPresent(app->ren);
}

App new_App(void) {
    App app = { 0 };
    app.win = SDL_CreateWindow(
        "mmben", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH*SCALE, HEIGHT*SCALE, 0);
    app.ren = SDL_CreateRenderer(app.win, -1, 0);
    SDL_RenderSetLogicalSize(app.ren, WIDTH, HEIGHT);
    SDL_RenderSetIntegerScale(app.ren, 1);
    return app;
}

void App_free(App *app) {
}

void App_run(App *app) {
    SDL_Event e;
    while (app->win) {
        while (SDL_PollEvent(&e))
            App_handle_event(app, e);
        App_step(app);
        App_draw(app);
    }
}

void App_run_many(App *apps, int n) {
    SDL_Event e;
    for (int instances=n; instances;) {
        instances = n;
        while(SDL_PollEvent(&e))
            for (int i=0; i<n; ++i)
                if (apps[i].win)
                    App_handle_event(&apps[i], e);
        for (int i=0; i<n; ++i)
            if (apps[i].win) {
                App_step(&apps[i]);
                App_draw(&apps[i]);
            } else
                --instances;
    }
}
