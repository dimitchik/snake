#include "fruit.h"

#include "basics.h"
#include "field.h"
#include "snake.h"

Fruit::Fruit(Field* field) : field(field) { spawn(); };
void Fruit::spawn() {
  bool is_on_snake = true;
  while (is_on_snake) {
    is_on_snake = false;
    coords.x = rand() % field->size_x;
    coords.y = rand() % field->size_y;
    for (int i = 0; i < field->snake->parts.size(); i++) {
      if (coords.x == field->snake->parts[i].coords.x &&
          coords.y == field->snake->parts[i].coords.y) {
        is_on_snake = true;
        break;
      }
    }
  }
}

void Fruit::hit_test(Snake* snake) {
  if (coords.x == snake->parts[0].coords.x &&
      coords.y == snake->parts[0].coords.y) {
    snake->grow();
    spawn();
  }
}
