#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <vector>
#include "gameObject.hpp"
#include "brick.hpp"
#include "brickgrid.hpp"
#include "paddle.hpp"
#include "ball.hpp"
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

    public:
        Game();
        void init(); //  Initialize SDL
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

        void setRunning(bool);
        void setLives(int);   

        void reset();
        void increaseScore(int);
        void increaseLevel();
};
#endif // GAME_H