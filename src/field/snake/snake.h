#pragma once

#include <iostream>
#include <vector>

#include "basics.h"

class Field;

class SnakePart {
 public:
  Coords coords;
  SnakePart(Coords coords);
};

class Snake {
 public:
  std::vector<SnakePart> parts;
  int speed = 1;
  Field* field;
  Snake(Coords coords, int length, Field* field);
  void move();
  bool hitTest();
  void setDirection(Direction direction);
  void grow();

 private:
  Direction direction = Direction::Up;
};
