#ifndef BALL_H
#define BALL_H
#include "gameObject.hpp"
#include "structs.hpp"
#include "brick.hpp"
/**
 * @brief Represents a ball in the game.
 *
 * Inherits from GameObject.
 */
class Ball: public GameObject
{
    private:
     velocity m_velocity;

    public:
     /**
      * @brief Constructor for Ball class.
      *
      * @param renderer The SDL renderer to render the ball.
      * @param pos Initial position of the ball.
      * @param size Size of the ball.
      * @param vel Initial velocity of the ball.
      *
      * Initializes the image of the ball.
      */
     Ball(SDL_Renderer* renderer, const position& pos, const objectSize& size,
          const velocity& vel);
     /**
      * @brief Constructor for Ball class.
      *
      * @param pos Initial position of the ball.
      * @param size Size of the ball.
      * @param vel Initial velocity of the ball.
      */
     Ball(position& pos, objectSize& size, velocity& vel);
     ~Ball() override;
     void update() override;
     /**
      * @brief Draws the ball on the screen.
      *
      * @param renderer The SDL renderer to render the ball.
      */
     void draw(SDL_Renderer* renderer) override;
     /**
      * @brief Checks collision with another game object.
      * Specific collision detection for hexagonal bricks.
      * Bounding box collision detection for other objects.
      *
      * @param obj The other game object.
      * @return True if collision occurs, false otherwise.
      */
     bool collidesWith(const GameObject& obj) const override;

     void setVelocityX(double x);
     void setVelocityY(double y);
     void setPositionX(double x);
     void setPositionY(double y);

     double getVelocityX() const;
     double getVelocityY() const;
     const velocity& getVelocity() const;
};
#endif // BALL_H