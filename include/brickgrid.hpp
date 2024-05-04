#ifndef BRICKGRID_H
#define BRICKGRID_H

#include <fstream>
#include <memory>
#include <vector>

#include "brick.hpp"
#include "gameObject.hpp"
#include "structs.hpp"

/**
 * @brief Brick Grid abstract class.
 *
 */
class BrickGrid
{
 protected:
  std::vector<std::vector<std::shared_ptr<Brick>>> m_bricks;
  int m_rows;
  int m_cols;
  int m_brickWidth;
  int m_brickHeight;

 public:
  BrickGrid(int rows, int cols, int brickWidth, int brickHeight);
  BrickGrid(int brickWidth, int brickHeight);
  virtual ~BrickGrid() {}

  virtual void initGridFromFile(const std::string& filename, const int initX,
                                const int initY) = 0;
  virtual void draw(SDL_Renderer* renderer) = 0;
  virtual void update() = 0;
  virtual std::vector<std::vector<std::shared_ptr<Brick>>>& getBricks() = 0;
  virtual void setRows(int rows) = 0;
  virtual bool allBricksDestroyed() = 0;

};

/**
 * @brief Classic Brick Grid class.
 * Implements a grid with classic rectangular bricks.
 *
 */
class ClassicBrickGrid : public BrickGrid {
 public:
  ClassicBrickGrid(int rows, int cols, int brickWidth, int brickHeight);
  ClassicBrickGrid(int brickWidth, int brickHeight);
  ~ClassicBrickGrid();

  void initGridFromFile(const std::string& filename, const int initX,
                        const int initY) override;
  void draw(SDL_Renderer* renderer) override;
  void update() override;
  std::vector<std::vector<std::shared_ptr<Brick>>>& getBricks() override;
  void setRows(int rows) override;
  bool allBricksDestroyed() override;
};

/**
 * @brief Hexagonal Brick Grid class.
 * Implements a grid with hexagonal bricks.
 *
 */
class HexagonalBrickGrid : public BrickGrid {
 public:
  HexagonalBrickGrid(int rows, int cols, int brickWidth, int brickHeight);
  HexagonalBrickGrid(int brickWidth, int brickHeight);
  ~HexagonalBrickGrid();

  void initGridFromFile(const std::string& filename, const int initX,
                        const int initY) override;
  void draw(SDL_Renderer* renderer) override;
  void update() override;
  std::vector<std::vector<std::shared_ptr<Brick>>>& getBricks() override;
  void setRows(int rows) override;
  bool allBricksDestroyed() override;
};

#endif // BRICKGRID_H