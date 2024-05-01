#ifndef BRICK_H
#define BRICK_H
#include <SDL2/SDL2_gfxPrimitives.h>

#include <iostream>
#include <vector>

#include "gameObject.hpp"
#include "structs.hpp"
class Brick : public GameObject {
 protected:
  bool m_destroyed;
  typeBrick m_type;

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
  void printProperties() const;
  const typeBrick& getType();
  void setType(typeBrick type);
};

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

class HexagonalBrick : public Brick {
 private:
  double m_q;  // Axial q-coordinate
  double m_r;  // Axial r-coordinate
  double m_radius;
  SDL_Renderer* m_renderer;

 public:
  HexagonalBrick(double q, double r, objectSize size, typeBrick type);
  void draw(SDL_Renderer* renderer) override;
  void draw(SDL_Renderer* renderer, Color color);
  void update() override;
  bool collidesWith(const GameObject& obj) const override;
  std::vector<position> getVertices() const;
  SDL_Rect getBoundingBox() const override;
};

#endif // BRICK_H