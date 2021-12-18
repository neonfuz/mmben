#include "gamelib.h"
#include "mmben.h"

typedef struct {
    size_t time;
    SDL_Texture *stage;
    SDL_Point cursor;
} mmben_data;

static void mmben_init(App *app) {
    mmben_data *data = app->data;
    data->stage = IMG_LoadTexture(app->ren, "./wad/mmbn6/stage1.png");
}
static void mmben_free(App *app) {
    mmben_data *data = app->data;
    SDL_DestroyTexture(data->stage);
}
static void mmben_step(App *app) {
    mmben_data *data = app->data;
    ++data->time;
    SDL_GetMouseState(&data->cursor.x, &data->cursor.y);
    data->cursor.x /= app->game.scale;
    data->cursor.y /= app->game.scale;
}
static void draw_stage(SDL_Renderer *ren, SDL_Texture *stage) {
    SDL_Rect sides[2] = {
         0, 0, 40, 78,
        40, 0, 40, 78
    };
    SDL_Rect out = {
        0, 72, 40, 78
    };
    for (int i=0; i<6; ++i) {
        SDL_RenderCopy(ren, stage, &sides[i/3], &out);
        out.x += 40;
    }
}
static void draw_cursor(SDL_Renderer *ren, SDL_Point cursor) {
    SDL_Rect rect = {cursor.x, cursor.y, 10, 10};
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderDrawRect(ren, &rect);

}
static void mmben_draw(App *app) {
    mmben_data *data = app->data;
    draw_stage(app->ren, data->stage);
    draw_cursor(app->ren, data->cursor);
}
const Game mmben = {
    .width = 240, .height = 160, .scale = 2, .data_size = sizeof(mmben_data),
    mmben_init, mmben_step, mmben_draw, mmben_free,
};
