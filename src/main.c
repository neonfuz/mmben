#include "gamelib.h"
#include "mmben.h"

int main() {
  Game games[] = { mmben, mmben };
  return Game_run_many(games, LENGTH(games));
}
