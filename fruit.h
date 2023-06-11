#include <SDL2/SDL.h>

#include "basics.h"
#include "snake.h"

class Fruit {
 public:
  Coords coords;
  Snake* snake;
  Fruit(int field_size_x, int field_size_y, Snake* snake)
      : field_size_x(field_size_x),
        field_size_y(field_size_y),
        snake(snake){

        };

 private:
  int field_size_x;
  int field_size_y;
};