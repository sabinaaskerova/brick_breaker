/**
 * @file Game.h
 * @brief Declaration of the Game class.
 *
 * This file declares the main Game class responsible for managing the game
 * logic. It handles game initialization, updating game state, rendering game
 * objects, and managing game events.
 */

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

/**
 * @brief The main game class responsible for managing the game logic.
 */
class Game{
    private:
        bool m_isWinner;
        Uint32 m_frameStart;     /**< The starting time of the frame. */
        SDLWrapper m_sdlWrapper; /**< SDL wrapper instance for handling SDL
                                    initialization. */

        std::default_random_engine
            m_randomEngine; /**< Random number generator engine. */
        std::uniform_int_distribution<int>
            m_distribution; /**< Uniform distribution for generating random
                               numbers. */
        int m_boostTimer;   /**< Timer for generating boosts. */

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
        /**
         * @brief Constructor for the Game class.
         *
         * @param gridType The type of grid for the game.
         * @param gridNumber The number of the grid for the game.
         */
        Game(const std::string& gridType, const int gridNumber);
        ~Game();
        /**
         * @brief Main game loop responsible for updating and rendering the
         * game.
         */
        void game_loop();

        /**
         * @brief Updates the game state.
         */
        void update();

        /**
         * @brief Updates the state of the balls in the game.
         */
        void updateBalls();

        /**
         * @brief Generates boosts at random intervals.
         */
        void generateBoosts();
        /**
         * @brief Updates the state of the boosts in the game.
         */
        void updateBoosts();

        /**
         * @brief Draws the game objects on the screen.
         */
        void draw();

        /**
         * @brief Draws a "Game Over", "You Win" messages on the screen.
         *
         * @param text The text to display.
         * @param x The x-coordinate of the text position.
         * @param y The y-coordinate of the text position.
         */
        void drawMessage(const std::string& text, int x, int y);

        /**
         * @brief Handles collision between game objects.
         *
         * @param ball The ball object involved in the collision.
         * @param gameObject The game object involved in the collision.
         */
        void handleCollision(Ball* ball, GameObject* gameObject);

        /**
         * @brief Applies the effect of a boost to the game.
         *
         * @tparam T The type of boost.
         * @param boost The boost object to apply.
         */
        template <typename T>
        void applyBoost(const T& boost);

        template <typename T>
         /**
         * @brief Ends the effect of a boost in the game.
         * 
         * @tparam T The type of boost.
         * @param boost The boost object to end.
         */
        void endBoost(const T& boost);

};
#endif // GAME_H