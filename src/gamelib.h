#include <SDL2/SDL.h>

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

int Game_run(Game game);
int Game_run_many(Game *games, int n);
