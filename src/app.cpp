#include "Graphics.hpp"
#include "FrameCounting.hpp"

int app() {
  static_assert(WIDTH_IN_PIXEL % RADIUS == 0);
  static_assert( HEIGHT_IN_PIXEL % RADIUS == 0);

  GameOfLife gol{};
  GameOfLife_init(&gol);
  GameOfLife_next_field(&gol);

  while (true) {
      GameOfLife_next_field(&gol);

      for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
          Graphics_put_pixel(x, y, RADIUS, GameOfLife_get_coord(&gol, x, y) ? 0xFFFFFFFF : 0x00000000);
        }
      }
      Graphics_flush();
    }
}

int main() {
  app();
}
