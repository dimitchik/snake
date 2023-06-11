#include "basics.h"

Direction opposite(Direction direction) {
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