#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "snake.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int PIXEL_SIZE = 10;

void render_frame(SDL_Window *window, SDL_Surface *screenSurface, Snake snake) {
  SDL_FillRect(screenSurface, NULL,
               SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
  for (int i = 0; i < snake.parts.size(); i++) {
    SDL_Rect rect = {
      x : snake.parts[i].coords.x * PIXEL_SIZE,
      y : snake.parts[i].coords.y * PIXEL_SIZE,
      w : PIXEL_SIZE,
      h : PIXEL_SIZE,
    };
    SDL_FillRect(screenSurface, &rect,
                 SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  }
  SDL_UpdateWindowSurface(window);
}

int init(SDL_Window **window, SDL_Surface **screenSurface) {
  const int init_result = SDL_Init(SDL_INIT_VIDEO);
  if (init_result < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return init_result;
  }
  *window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (*window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }
  const int ttf_init_result = TTF_Init();
  if (ttf_init_result < 0) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    return ttf_init_result;
  }
  *screenSurface = SDL_GetWindowSurface(*window);
  return 0;
}

void game_over_screen(SDL_Window *window, SDL_Surface *screenSurface,
                      TTF_Font *font) {
  SDL_FillRect(screenSurface, NULL,
               SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
  SDL_Surface *game_over_text =
      TTF_RenderText_Solid(font, "GAME OVER", {0xFF, 0xFF, 0xFF});
  const int text_width = game_over_text->w;
  const int text_height = game_over_text->h;
  SDL_Rect text_rect = {
    x : (SCREEN_WIDTH - text_width) / 2,
    y : (SCREEN_HEIGHT - text_height) / 2,
    w : text_width,
    h : text_height,
  };
  SDL_BlitSurface(game_over_text, NULL, screenSurface, &text_rect);
  SDL_UpdateWindowSurface(window);
  SDL_FreeSurface(game_over_text);
}

int main(int argc, char *args[]) {
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;
  const int init_result = init(&window, &screenSurface);
  TTF_Font *font = NULL;
  font = TTF_OpenFont("quadrangle.ttf", 28);
  if (init_result < 0) return init_result;
  Snake snake =
      Snake({40, 40}, 5, SCREEN_WIDTH / PIXEL_SIZE, SCREEN_HEIGHT / PIXEL_SIZE);
  render_frame(window, screenSurface, snake);
  SDL_Event e;
  bool quit = false;
  bool game_over = false;
  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) quit = true;
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_DOWN:
            snake.setDirection(Direction::Down);
            break;
          case SDLK_UP:
            snake.setDirection(Direction::Up);
            break;
          case SDLK_LEFT:
            snake.setDirection(Direction::Left);
            break;
          case SDLK_RIGHT:
            snake.setDirection(Direction::Right);
            break;
          case SDLK_ESCAPE:
            quit = true;
            break;
        }
      }
    }
    if (game_over) continue;
    SDL_Delay(100);
    snake.move();
    if (snake.hitTest()) {
      game_over = true;
      game_over_screen(window, screenSurface, font);
      continue;
    }
    render_frame(window, screenSurface, snake);
  }
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
