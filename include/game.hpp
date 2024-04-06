#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <vector>
#include "gameObject.hpp"
#include "brick.hpp"
#include "brickgrid.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include <iostream>
#include "structs.hpp"
#include <memory>
#include <cassert>

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
        bool gameOver;
        bool running;
        
        Ball* m_ball;
        std::unique_ptr<Paddle> m_paddle;
        std::unique_ptr<BrickGrid> m_brickGrid;
        std::vector<std::unique_ptr<Ball>> m_balls;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
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


        void setGameOver(bool);
        const bool getGameOver();
        const int& getScore();
        const int& getLevel();
        const int getLives();
        const bool getRunning();
        BrickGrid& getBrickGrid();

        std::unique_ptr<Paddle>& getPaddle();


        void setRunning(bool);
        void setLives(int);   

        void reset();
        void increaseScore(int);
        void increaseLevel();
};
#endif // GAME_H