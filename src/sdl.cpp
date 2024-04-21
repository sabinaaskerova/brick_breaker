#include "sdl.hpp"
SDLWrapper::SDLWrapper() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return;
  }
}
SDLWrapper::SDLWrapper(Uint32 flags) {
  if (SDL_Init(flags) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return;
  }
  if (TTF_Init() == -1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }
}

void SDLWrapper::init(Uint32 flags) {}
SDLWrapper::~SDLWrapper() {
  // SDL_DestroyRenderer(renderer);
  // SDL_DestroyWindow(window);
  SDL_Quit();
}

SDL_Window* SDLWrapper::createWindow(const char* title, int x, int y, int w,
                                     int h, Uint32 flags) {
  SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);

  if (window == nullptr) {
    throw std::runtime_error(SDL_GetError());
  }
  return window;
}

SDL_Renderer* SDLWrapper::createRenderer(SDL_Window* window, int index,
                                         Uint32 flags) {
  SDL_Renderer* renderer = SDL_CreateRenderer(window, index, flags);
  if (renderer == nullptr) {
    throw std::runtime_error(SDL_GetError());
  }
  return renderer;
}