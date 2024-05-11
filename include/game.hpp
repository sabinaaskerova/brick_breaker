#ifndef GAME_H
#define GAME_H
#include </usr/include/SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "ball.hpp"
#include "boost.hpp"
#include "brick.hpp"
#include "brickgrid.hpp"
#include "gameObject.hpp"
#include "paddle.hpp"
#include "sdl.hpp"
#include "structs.hpp"
#include "wall.hpp"

enum GameStates{
    MENU,
    PLAY,
    PAUSE,
    GAMEOVER
};
class Game{
    private:
        bool m_isWinner;
        Uint32 m_frameStart;
        SDLWrapper m_sdlWrapper;

        std::default_random_engine m_randomEngine;
        std::uniform_int_distribution<int> m_distribution;
        int m_boostTimer;
        
        std::unique_ptr<Paddle> m_paddle;
        std::unique_ptr<BrickGrid> m_brickGrid;
        std::deque<std::unique_ptr<Ball>> m_balls;
        int m_numBalls;
        std::unique_ptr<Wall> m_wall;
        std::deque<std::unique_ptr<Boost>> m_boosts;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        SDL_Texture  *m_image;
        SDL_Rect      m_render_viewport;
        SDL_Event     m_window_event;

    public:
        Game();
        Game(const std::string& gridType, const int gridNumber);
        ~Game();
        void game_loop();
        void update();
        
        void updateBalls();
        void generateBoosts();
        void updateBoosts();

        void draw();  
        void drawMessage(const std::string& text, int x, int y);  

        void handleCollision(Ball* ball, GameObject* gameObject);

        template <typename T>
        void applyBoost(const T& boost);

        template <typename T>
        void endBoost(const T& boost);

};
#endif // GAME_H