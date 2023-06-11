#include <iostream>
#include <vector>

#include "basics.h"

class SnakePart {
 public:
  Coords coords;
  SnakePart(Coords coords) : coords(coords) {
    std::cout << "SnakePart created" << std::endl;
  };
};

class Snake {
 public:
  std::vector<SnakePart> parts;
  int speed = 1;
  int field_size_x;
  int field_size_y;
  Snake(Coords coords, int length, int field_size_x, int field_size_y)
      : field_size_x(field_size_x), field_size_y(field_size_y) {
    for (int i = 0; i < length; i++) {
      parts.push_back(SnakePart(coords));
    }
  }
  void move() {
    for (int i = parts.size(); i > 0; i--) {
      parts[i].coords = parts[i - 1].coords;
    }
    parts[0].coords.move(direction, speed);
  }
  bool hitTest() {
    Coords head = parts[0].coords;
    if (head.x < 0 || head.x > field_size_x || head.y < 0 ||
        head.y > field_size_y) {
      return true;
    }
    for (int i = 1; i < parts.size(); i++) {
      if (head.x == parts[i].coords.x && head.y == parts[i].coords.y) {
        return true;
      }
    }
    return false;
  }
  void setDirection(Direction direction) {
    if ((opposite(direction) == this->direction)) return;
    this->direction = direction;
  }

 private:
  Direction direction = Direction::Left;
};
