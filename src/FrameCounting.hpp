#pragma once

#include "defs.h"

struct GameOfLife {
  bool field[WIDTH * HEIGHT];
};

void GameOfLife_init(GameOfLife* game_of_life);

int GameOfLife_get_alive_cells(GameOfLife* game_of_life, int x, int y);

void GameOfLife_next_field(GameOfLife* game_of_life);

bool GameOfLife_get_coord(GameOfLife* game_of_life, int x, int y);
