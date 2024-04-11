#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>

#include <vector>
#include "gameObject.hpp"
#include "brick.hpp"
#include "brickgrid.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include "wall.hpp"
#include "boost.hpp"
#include <iostream>
#include "structs.hpp"
#include </usr/include/SDL2/SDL_ttf.h>
#include <memory>
#include <cassert>
#include <deque>
#include <random>

enum GameStates{
    MENU,
    PLAY,
    PAUSE,
    GAMEOVER
};
class Game{
    private:
        int score;
        int level;
        int lives;
        bool running;
        bool m_isWinner;
        Uint32 m_frameStart;

        std::default_random_engine m_randomEngine;
        std::uniform_int_distribution<int> m_distribution;
        int m_boostTimer;
        
        std::unique_ptr<Paddle> m_paddle;
        std::unique_ptr<BrickGrid> m_brickGrid;
        std::vector<std::unique_ptr<Ball>> m_balls;
        int m_numBalls;
        std::unique_ptr<Wall> m_wall;
        std::deque<std::unique_ptr<Boost>> m_boosts;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        SDL_Texture* backgroundImage;
        SDL_Texture  *m_image;
        SDL_Rect      m_render_viewport;
        SDL_Event     m_window_event;

    public:
        Game();
        ~Game();
        void init();
        void game_loop();
        void update();

        void render();
        void handleEvents();
        void clean();
        void draw();  
        void drawMessage(const std::string& text, int x, int y);  


        void setGameOver(bool);
        const bool getGameOver();
        const int& getScore();
        const int& getLevel();
        const int getLives();
        const bool getRunning();
        BrickGrid& getBrickGrid();
        void handleCollision(Ball* ball, GameObject* gameObject);

        std::unique_ptr<Paddle>& getPaddle();


        void setRunning(bool);
        void setLives(int);   

        void reset();
        void increaseScore(int);
        void increaseLevel();
};
#endif // GAME_H