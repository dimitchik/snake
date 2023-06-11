#pragma once

#include <SDL2/SDL.h>

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
  void render(SDL_Surface* screenSurface);

 private:
  Direction rendered_direction;
  Direction direction = Direction::Up;
};
