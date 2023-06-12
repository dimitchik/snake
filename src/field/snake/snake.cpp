#include "snake.h"

#include "basics.h"
#include "constants.h"
#include "field.h"

SnakePart::SnakePart(Coords coords) : coords(coords){};

Snake::Snake(Coords coords, int length, Field *field) : field(field) {
  for (int i = 0; i < length; i++) {
    parts.push_back(SnakePart(coords));
  }
}
void Snake::move() {
  for (int i = parts.size(); i > 0; i--) {
    parts[i].coords = parts[i - 1].coords;
  }
  parts[0].coords.move(direction, speed);
}
bool Snake::hitTest() {
  Coords head = parts[0].coords;
  if (head.x < 0 || head.x >= field->size_x || head.y < 0 ||
      head.y >= field->size_y) {
    return true;
  }
  for (int i = 1; i < parts.size(); i++) {
    if (head.x == parts[i].coords.x && head.y == parts[i].coords.y) {
      return true;
    }
  }
  return false;
}
void Snake::setDirection(Direction new_direction) {
  if ((opposite(new_direction, direction) == rendered_direction)) return;
  direction = new_direction;
}
void Snake::grow() {
  parts.push_back(SnakePart(parts[parts.size() - 1].coords));
}
void Snake::render(SDL_Surface *screenSurface) {
  for (int i = 0; i < parts.size(); i++) {
    SDL_Rect rect = {
        .x = parts[i].coords.x * PIXEL_SIZE,
        .y = parts[i].coords.y * PIXEL_SIZE,
        .w = PIXEL_SIZE,
        .h = PIXEL_SIZE,
    };
    SDL_FillRect(screenSurface, &rect,
                 SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  }
  rendered_direction = direction;
}