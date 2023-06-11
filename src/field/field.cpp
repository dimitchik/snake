#include "field.h"

#include "fruit.h"
#include "snake.h"

Field::Field(int size_x, int size_y)
    : size_x(size_x),
      size_y(size_y),
      snake(new Snake({size_x / 2, size_y / 2}, 5, this)),
      fruit(new Fruit(this)){};
Field::~Field() {
  delete snake;
  delete fruit;
}