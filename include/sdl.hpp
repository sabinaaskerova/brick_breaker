#ifndef SDL_HPP
#define SDL_HPP
#include </usr/include/SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include <stdexcept>
/**
 * @brief A class for managing SDL initialization and resource creation.
 */
class SDLWrapper {
 public:
  SDLWrapper();
  /**
   * @brief Constructor with flags for SDL initialization.
   * @param flags Initialization flags for SDL.
   */
  SDLWrapper(Uint32 flags);
  ~SDLWrapper();
  /**
   * @brief Create an SDL window.
   * @param title The title of the window.
   * @param x The x-coordinate of the window position.
   * @param y The y-coordinate of the window position.
   * @param w The width of the window.
   * @param h The height of the window.
   * @param flags The flags used to create the window.
   * @return A pointer to the created SDL window.
   */
  SDL_Window* createWindow(const char* title, int x, int y, int w, int h,
                           Uint32 flags);
  /**
   * @brief Create an SDL renderer.
   * @param window The SDL window to associate the renderer with.
   * @param index The index of the rendering driver to use (-1 for the first
   *              available driver).
   * @param flags The flags used to create the renderer.
   * @return A pointer to the created SDL renderer.
   */
  SDL_Renderer* createRenderer(SDL_Window* window, int index, Uint32 flags);

};

#endif