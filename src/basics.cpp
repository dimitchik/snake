#include "basics.h"

Direction opposite(Direction direction, Direction default_direction) {
  if (opposite_direction.find(direction) == opposite_direction.end()) {
    return default_direction;
  }
  return opposite_direction.at(direction);
}

void Coords::move(Direction direction, int amount) {
  switch (direction) {
    case Direction::Down:
      y += amount;
      break;
    case Direction::Left:
      x -= amount;
      break;
    case Direction::Right:
      x += amount;
      break;
    case Direction::Up:
      y -= amount;
  }
}