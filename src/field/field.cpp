#include "field.h"

#include <SDL2/SDL.h>

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

void Field::render(SDL_Window *window, SDL_Surface *screenSurface) {
  SDL_FillRect(screenSurface, NULL,
               SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
  snake->render(screenSurface);
  fruit->render(screenSurface);
  SDL_UpdateWindowSurface(window);
}