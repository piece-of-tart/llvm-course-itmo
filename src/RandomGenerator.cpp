#include "RandomGenerator.hpp"
#include <cstdlib>
#include <ctime>

void RandomGenerator_set_seed() {
  static bool flag = true;
  if (flag) {
    srand(time(nullptr));
  }
  flag = false;
}

int RandomGenerator_next_int() {
  RandomGenerator_set_seed();
  return rand();
}
