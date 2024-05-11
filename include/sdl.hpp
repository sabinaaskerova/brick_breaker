#ifndef SDL_HPP
#define SDL_HPP
#include </usr/include/SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include <stdexcept>
class SDLWrapper {
 public:
  SDLWrapper();
  SDLWrapper(Uint32 flags);
  ~SDLWrapper();

  SDL_Window* createWindow(const char* title, int x, int y, int w, int h,
                           Uint32 flags);
  SDL_Renderer* createRenderer(SDL_Window* window, int index, Uint32 flags);

  void init(Uint32 flags);
};

#endif