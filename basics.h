enum class Direction { Left, Up, Right, Down };

Direction opposite(Direction direction) {
  switch (direction) {
    case Direction::Left:
      return Direction::Right;
    case Direction::Up:
      return Direction::Down;
    case Direction::Right:
      return Direction::Left;
    case Direction::Down:
      return Direction::Up;
  }
}

struct Coords {
  int x;
  int y;
  void move(Direction direction, int amount) {
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
};
