#ifndef BRICK_H
#define BRICK_H
#include <SDL2/SDL2_gfxPrimitives.h>

#include <iostream>
#include <vector>

#include "gameObject.hpp"
#include "structs.hpp"
/**
 * @brief Represents a brick in the game.
 *
 * Inherits from GameObject.
 */
class Brick : public GameObject {
 protected:
  bool m_destroyed;
  typeBrick m_type;  // Type of the brick: NORMAL, DOUBLE, TRIPLE, EMPTY

 public:
  Brick(position pos, objectSize size, typeBrick type);
  virtual ~Brick();

  virtual void update() override = 0;
  virtual void draw(SDL_Renderer* renderer) override = 0;

  virtual bool collidesWith(const GameObject& obj) const override = 0;
  bool isDestroyed() const;

  position getPosition() const;
  objectSize getSize() const;
  void setDestroyed(bool destroyed);
  virtual SDL_Rect getBoundingBox() const = 0;
  const typeBrick& getType() const;
  void setType(typeBrick type);
};
/**
 * @brief Represents a classic rectangular brick in the game.
 */
class ClassicBrick : public Brick {
 public:
  ClassicBrick(position pos, objectSize size, typeBrick type);
  ~ClassicBrick();
  void update() override;
  void draw(SDL_Renderer* renderer) override;
  bool collidesWith(const GameObject& obj) const override;
  void setDestroyed(bool destroyed);
  SDL_Rect getBoundingBox() const override;
};
/**
 * @brief Represents a hexagonal brick in the game.
 */
class HexagonalBrick : public Brick {
 private:
  double m_q;      /**< Axial q-coordinate of the hexagonal brick. */
  double m_r;      /**< Axial r-coordinate of the hexagonal brick. */
  double m_radius; /**< Radius of the hexagonal brick. */
  SDL_Renderer* m_renderer;

 public:
  /**
   * @brief Constructor for HexagonalBrick class.
   *
   * @param q Axial q-coordinate of the brick.
   * @param r Axial r-coordinate of the brick.
   * @param size Size of the brick.
   * @param type Type of the brick.
   */
  HexagonalBrick(double q, double r, objectSize size, typeBrick type);
  void draw(SDL_Renderer* renderer) override;
  /**
   * @brief Draws the hexagonal brick with a specified color.
   *
   * @param renderer The SDL renderer to render the brick.
   * @param color The color to use.
   */
  void draw(SDL_Renderer* renderer, Color color);
  void update() override;
  bool collidesWith(const GameObject& obj) const override;
  /**
   * @brief Gets the vertices of the hexagonal brick.
   *
   * @return A vector containing the vertices of the hexagonal brick.
   */
  std::vector<position> getVertices() const;
  /**
   * @brief Gets the expanded bounding box of the hexagonal brick including all
   * vertices.
   *
   * @return The bounding box of the hexagonal brick.
   */
  SDL_Rect getBoundingBox() const override;
};

#endif // BRICK_H