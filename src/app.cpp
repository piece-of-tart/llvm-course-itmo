#include "sim.h"

#define WIDTH_IN_PIXEL 1200
#define HEIGHT_IN_PIXEL 800
#define RADIUS 10

#define WIDTH (WIDTH_IN_PIXEL / RADIUS)
#define HEIGHT (HEIGHT_IN_PIXEL / RADIUS)

struct GameOfLife {
  bool field[WIDTH * HEIGHT];
};

static void GameOfLifeInit(GameOfLife *game_of_life) {
  static int rand = 2463534242u;
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      game_of_life->field[y * WIDTH + x] = rand % 2 == 0;
      rand ^= rand << 13;
      rand ^= rand >> 17;
      rand ^= rand << 5;
    }
  }
}

static int GameOfLifeGetAliveCells(GameOfLife *game_of_life, int x, int y) {
  int cnt = 0;
  for (int x_diff = -1; x_diff < 2; x_diff++) {
    for (int y_diff = -1; y_diff < 2; y_diff++) {
      if (x_diff == 0 && y_diff == 0) {
        continue;
      }
      if (game_of_life->field[((y + y_diff + HEIGHT) % HEIGHT) * WIDTH + (x + x_diff + HEIGHT) % HEIGHT]) {
        ++cnt;
      }
    }
  }
  return cnt;
}

static void GameOfLifeNextField(GameOfLife *game_of_life) {
  bool new_field[WIDTH * HEIGHT];
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      int live_neighbours = GameOfLifeGetAliveCells(game_of_life, x, y);
      int idx = y * WIDTH + x;
      bool alive = game_of_life->field[idx];
      if (!alive && live_neighbours == 3) {
        new_field[idx] = true;
      } else if (alive && live_neighbours != 2 && live_neighbours != 3) {
        new_field[idx] = false;
      } else {
        new_field[idx] = game_of_life->field[idx];
      }
    }
  }

  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      game_of_life->field[i * WIDTH + j] = new_field[i * WIDTH + j];
    }
  }
}

static bool GameOfLifeGetCoord(GameOfLife *game_of_life, int x, int y) {
  return game_of_life->field[y * WIDTH + x];
}

int app() {
  static_assert(WIDTH_IN_PIXEL % RADIUS == 0);
  static_assert(HEIGHT_IN_PIXEL % RADIUS == 0);

  GameOfLife gol{};
  GameOfLifeInit(&gol);
  GameOfLifeNextField(&gol);

  while (true) {
    GameOfLifeNextField(&gol);

    for (int x = 0; x < WIDTH; ++x) {
      for (int y = 0; y < HEIGHT; ++y) {
        Graphics_put_pixel(x, y, RADIUS, GameOfLifeGetCoord(&gol, x, y) ? 0xFFFFFFFF : 0x00000000);
      }
    }
    Graphics_flush();
  }
}

int main() {
  app();
}
