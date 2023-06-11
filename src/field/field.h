#pragma once

#include "fruit.h"
#include "snake.h"

class Field {
 public:
  int size_x;
  int size_y;
  Snake* snake;
  Fruit* fruit;
  Field(int size_x, int size_y);
  ~Field();
};