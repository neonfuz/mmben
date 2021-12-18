#include "app.h"

typedef struct {
    size_t time;
} mmben_data;

void mmben_init() {}
void mmben_free() {}

void mmben_step(App *app) {
    mmben_data *data = app->data;
    ++data->time;
}

void mmben_draw(App *app) {
    mmben_data *data = app->data;
    size_t time = data->time;
    if (time % 60 == 0)
        printf("%ld\n", time/60);
}

static const
Game mmben = {
    .width = 240, .height = 160, .scale = 2, .data_size = sizeof(mmben_data),
    mmben_init, mmben_step, mmben_draw, mmben_free,
};

int main() { return Game_run(mmben); }
