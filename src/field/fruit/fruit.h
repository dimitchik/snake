#pragma once

#include <SDL2/SDL.h>

#include "basics.h"

class Field;
class Snake;

class Fruit {
 public:
  Coords coords;
  Field* field;
  Fruit(Field* field);
  void spawn();
  void hit_test(Snake* snake);
};
