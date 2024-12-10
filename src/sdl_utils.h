#ifndef TORTEM_SDL_UTIL_H
#define TORTEM_SDL_UTIL_H
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

static int init_sdl(int width, int height, char* window_title , SDL_Window** sdl_window, SDL_Renderer** sdl_renderer) {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Could not init SDL!: Error: %s\n", SDL_GetError());
    return 0;
  }
  *sdl_window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  if (*sdl_window == NULL) {
      fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return 0;
  }
  *sdl_renderer = SDL_CreateRenderer(*sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (*sdl_renderer == NULL) {
      fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
      return 0;
  }
  return 1;
}


static void free_sdl(SDL_Texture* texture, SDL_Window* window, SDL_Renderer* renderer) {
  if (texture != NULL) {
    SDL_DestroyTexture(texture);
  }
  if (renderer != NULL) {
    SDL_DestroyRenderer(renderer);
  }
  if (window != NULL) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}
#endif
