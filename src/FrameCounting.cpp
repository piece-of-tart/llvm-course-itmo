#include "FrameCounting.hpp"
#include "RandomGenerator.hpp"

void GameOfLife_init(GameOfLife* game_of_life) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      game_of_life->field[y * WIDTH + x] = RandomGenerator_next_int() % 2 == 0;
    }
  }
}

int GameOfLife_get_alive_cells(GameOfLife* game_of_life, int x, int y) {
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

void GameOfLife_next_field(GameOfLife* game_of_life) {
  bool new_field[WIDTH * HEIGHT];
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      int live_neighbours = GameOfLife_get_alive_cells(game_of_life,x, y);
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

bool GameOfLife_get_coord(GameOfLife* game_of_life, int x, int y) {
  return game_of_life->field[y * WIDTH + x];
}
