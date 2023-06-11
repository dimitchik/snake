#pragma once
#include <map>

enum class Direction { Left, Up, Right, Down };
Direction opposite(Direction direction, Direction default_direction);
const std::map<Direction, Direction> opposite_direction = {
    {Direction::Left, Direction::Right},
    {Direction::Up, Direction::Down},
    {Direction::Right, Direction::Left},
    {Direction::Down, Direction::Up},
};

struct Coords {
  int x;
  int y;
  void move(Direction direction, int amount);
};