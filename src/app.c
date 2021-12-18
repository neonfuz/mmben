#include "app.h"

App new_App(Game g) {
    App app = { 0 };
    app.win = SDL_CreateWindow(
        "mmben", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        g.width*g.scale, g.height*g.scale, 0);
    app.ren = SDL_CreateRenderer(app.win, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetLogicalSize(app.ren, g.width, g.height);
    SDL_RenderSetIntegerScale(app.ren, 1);
    app.game = g;
    app.data = calloc(1, g.data_size);
    g.init(&app);
    return app;
}

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
    app->game.step(app);
}

void App_draw(App *app) {
    SDL_RenderClear(app->ren);
    app->game.draw(app);
    SDL_RenderPresent(app->ren);
}

void App_free(App *app) {
     app->game.free(app);
     free(app->data);
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

int Game_run(Game g) {
    SDL_Init(SDL_INIT_EVERYTHING);
    App app = new_App(g);
    App_run(&app);
    SDL_Quit();
    return 0;
}
