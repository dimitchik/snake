#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdio.h>

#include "basics.h"
#include "constants.h"
#include "field.h"
#include "font.h"
#include "snake.h"

class GameState {
 public:
  SDL_Window *window;
  SDL_Surface *screenSurface;
  TTF_Font *font;
  Field *field;
  bool quit = false;
  GameState(SDL_Window *window, SDL_Surface *screenSurface, TTF_Font *font,
            Field *field)
      : window(window),
        screenSurface(screenSurface),
        font(font),
        field(field){};
};

int init(SDL_Window **window, SDL_Surface **screenSurface) {
  const int init_result = SDL_Init(SDL_INIT_VIDEO);
  if (init_result < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return init_result;
  }
  *window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED,
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
      .x = (SCREEN_WIDTH - text_width) / 2,
      .y = (SCREEN_HEIGHT - text_height) / 2,
      .w = text_width,
      .h = text_height,
  };
  SDL_BlitSurface(game_over_text, NULL, screenSurface, &text_rect);
  SDL_UpdateWindowSurface(window);
  SDL_FreeSurface(game_over_text);
}

void run_loop(GameState *game_state) {
  SDL_Event e;
  bool game_over = false;
  Direction direction;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) game_state->quit = true;
    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_DOWN:
          direction = Direction::Down;
          break;
        case SDLK_UP:
          direction = Direction::Up;
          break;
        case SDLK_LEFT:
          direction = Direction::Left;
          break;
        case SDLK_RIGHT:
          direction = Direction::Right;
          break;
        case SDLK_ESCAPE:
          game_state->quit = true;
          break;
        case SDLK_RETURN:
          if (game_over) {
            delete game_state->field;
            game_state->field = new Field(SCREEN_WIDTH / PIXEL_SIZE,
                                          SCREEN_HEIGHT / PIXEL_SIZE);
            game_over = false;
          }
          break;
      }
    }
  }
#ifdef __EMSCRIPTEN__
  if (game_state->quit) emscripten_cancel_main_loop();
#endif
  game_state->field->snake->setDirection(direction);
  if (game_over) return;
  SDL_Delay(100);
  game_state->field->snake->move();
  if (game_state->field->snake->hitTest()) {
    game_over = true;
    game_over_screen(game_state->window, game_state->screenSurface,
                     game_state->font);
    return;
  }
  game_state->field->fruit->hit_test(game_state->field->snake);
  game_state->field->render(game_state->window, game_state->screenSurface);
}

int main(int argc, char *args[]) {
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;
  const int init_result = init(&window, &screenSurface);
  TTF_Font *font = NULL;
  SDL_RWops *font_rw = SDL_RWFromConstMem(&font_data, font_length);
  font = TTF_OpenFontRW(font_rw, 1, 28);
  if (font == NULL) {
    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    return -1;
  }
  if (init_result < 0) return init_result;
  Field *field =
      new Field(SCREEN_WIDTH / PIXEL_SIZE, SCREEN_HEIGHT / PIXEL_SIZE);
  field->render(window, screenSurface);
  GameState *game_state = new GameState(window, screenSurface, font, field);
  game_state->quit = false;
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(reinterpret_cast<em_arg_callback_func>(run_loop),
                               game_state, 0, 1);
#else
  while (!game_state->quit) {
    run_loop(game_state);
  }
#endif
  delete game_state;
  delete field;
  TTF_CloseFont(font);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
