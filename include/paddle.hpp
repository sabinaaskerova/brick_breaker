/**
 * @file Paddle.h
 * @brief Declaration of the Paddle class.
 *
 * This file declares the Paddle class, which represents a paddle object in the
 * game. It inherits from the GameObject class and provides functionality
 * specific to paddles, such as handling input events, moving horizontally, and
 * managing paddle width and type.
 */

#ifndef PADDLE_H
#define PADDLE_H
#include "gameObject.hpp"
/**
 * @brief Enum representing the type of paddle.
 */
enum class PaddleType {
  NORMAL,  ///< Normal paddle type.
  WIDE,    ///< Wide paddle type.
  NARROW   ///< Narrow paddle type.
};
/**
 * @brief Class representing a paddle object in the game.
 */
class Paddle: public GameObject{   
    private:
        PaddleType m_type;     
    public:
     /**
      * @brief Constructor to initialize a paddle.
      * @param pos The position of the paddle.
      * @param size The size of the paddle.
      */
     Paddle(
         const position& pos,
         const objectSize& size);  // & because we are not copying the object
                                   // valgrind --leak-check=full ./your_program
     ~Paddle();
     void update() override;
     /**
      * @brief Draws the paddle rectangle on the screen.
      * @param renderer The SDL renderer.
      */
     void draw(SDL_Renderer* renderer) override;
     /**
      * @brief Handles nouse events for the paddle.
      * @param event The SDL event to handle.
      */
     void handle_input(const SDL_Event& event);
     /**
      * @brief Sets the width of the paddle.
      * @param width The width of the paddle.
      */
     void setWidth(int);

     bool collidesWith(const GameObject& obj) const override;
     /**
      * @brief Moves the paddle horizontally.
      * @param x The amount of pixels to move the paddle.
      */
     void move(int x);
     /**
      * @brief Gets the width of the paddle.
      * @return The width of the paddle.
      */
     const double& getWidth() const;
     /**
      * @brief Sets the type of the paddle.
      * @param type The type of the paddle.
      */
     void setType(PaddleType type);
     /**
      * @brief Gets the type of the paddle.
      * @return The type of the paddle.
      */
     const PaddleType& getType() const;
};


#endif // PADDLE_H