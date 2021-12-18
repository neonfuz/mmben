#include "app.h"

struct Game_data {
    size_t time;
};

void mmben_init(App *app) {}
void mmben_free(App *app) {}

void mmben_step(App *app) {
    ++app->data->time;
}

void mmben_draw(App *app) {
    size_t time = app->data->time;
    if (time % 60 == 0)
        printf("%ld\n", time/60);
}

static const
Game mmben = {
    .width = 240, .height = 160, .scale = 2, .data_size = sizeof(Game_data),
    mmben_init, mmben_step, mmben_draw, mmben_free,
};

int main() { return Game_run(mmben); }
