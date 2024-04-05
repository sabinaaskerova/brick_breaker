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
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        bool running;
        std::vector<GameObject*> m_gameObjects;
        BrickGrid* m_brickGrid;

    public:
        Game();
        ~Game();
        void init();
        void update(); 
        void render();
        void handleEvents();
        void clean();

        void setGameOver(bool);
        const bool getGameOver();
        const int& getScore();
        const int& getLevel();
        const int getLives();
        const bool getRunning();
        BrickGrid& getBrickGrid();

        void setRunning(bool);
        void setLives(int);   

        void reset();
        void increaseScore(int);
        void increaseLevel();
};
#endif // GAME_H