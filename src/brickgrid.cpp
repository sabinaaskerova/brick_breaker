/**
 * @file brickgrid.cpp
 * @brief Initializes and draws the brick grid.
 *
 */
#include "brickgrid.hpp"
#include <iostream>

BrickGrid::BrickGrid(int rows, int cols, int brickWidth, int brickHeight) : 
    m_rows(rows), m_cols(cols), m_brickWidth{brickWidth}, m_brickHeight{brickHeight} {}
    BrickGrid::BrickGrid(int brickWidth, int brickHeight) : 
    m_brickWidth{brickWidth}, m_brickHeight{brickHeight} {}

ClassicBrickGrid::ClassicBrickGrid(int rows, int cols, int brickWidth, int brickHeight) : 
    BrickGrid(rows, cols, brickWidth, brickHeight)
{
}
ClassicBrickGrid::ClassicBrickGrid(int brickWidth, int brickHeight) : 
   BrickGrid(brickWidth, brickHeight)
{
}

ClassicBrickGrid::~ClassicBrickGrid()
{
}

/**
 * @brief
 *
 * @param filename the name of the file containing the grid
 * @param initX the x position of the first brick
 * @param initY the y position of the first brick
 * @pre filename is a valid file
 * @pre file contains '#' for normal bricks, '*' for double bricks, '@' for
 * triple bricks, and ' ' for empty bricks
 * @post m_bricks contains the grid
 */
void ClassicBrickGrid::initGridFromFile(const std::string& filename,
                                        const int initX, const int initY) {
  const double padding = 5;
  std::ifstream file(filename);
  if (file.is_open()) {
    objectSize size = {m_brickWidth - padding, m_brickHeight - padding};
    std::string line;
    int rowNumber = 0;
    while (std::getline(file, line)) {
      std::vector<std::shared_ptr<Brick>> row;
      for (int colNumber = 0; colNumber < static_cast<int>(line.size());
           colNumber++) {
        char c = line[colNumber];

        position pos = {
            (colNumber * m_brickWidth) + static_cast<double>(initX),
            (rowNumber * m_brickHeight) + static_cast<double>(initY)};
        std::shared_ptr<Brick> brick = nullptr;
        switch (c) {
          case '#': {
            brick =
                std::make_shared<ClassicBrick>(pos, size, typeBrick::NORMAL);
            row.push_back(brick);
            break;
          }
          case '*': {
            brick =
                std::make_shared<ClassicBrick>(pos, size, typeBrick::DOUBLE);
            row.push_back(brick);
            break;
          }
          case '@': {
            brick =
                std::make_shared<ClassicBrick>(pos, size, typeBrick::TRIPLE);
            row.push_back(brick);
            break;
          }
          case ' ':
            brick = std::make_shared<ClassicBrick>(pos, size, typeBrick::EMPTY);
            row.push_back(brick);
            break;
        }
      }
      m_bricks.emplace_back(row);
      rowNumber++;
    }
  }
}
/**
 * @brief draws the grid
 *
 * @param renderer
 */
void ClassicBrickGrid::draw(SDL_Renderer* renderer){
    for (const std::vector<std::shared_ptr<Brick>>& row : m_bricks) {
        for (const std::shared_ptr<Brick>& brick : row) {
            if (brick != nullptr) {
              if (brick->getType() != typeBrick::EMPTY &&
                  !brick->isDestroyed()) {
                if (brick->getType() == typeBrick::NORMAL) {
                  SDL_SetRenderDrawColor(renderer, 255, 204, 255, 50);
                } else if (brick->getType() == typeBrick::DOUBLE) {
                  SDL_SetRenderDrawColor(renderer, 255, 51, 153, 250);
                } else if (brick->getType() == typeBrick::TRIPLE) {
                  SDL_SetRenderDrawColor(renderer, 153, 0, 153, 255);
                }
                brick->draw(renderer);
              }
            }
        }
    }
}
void ClassicBrickGrid::update(){
}

std::vector<std::vector<std::shared_ptr<Brick>>>& ClassicBrickGrid::getBricks()
{
    return m_bricks;
}

void ClassicBrickGrid::setRows(int rows) {
    m_rows = rows;
}

/**
 * @brief checks if all bricks are destroyed
 * used to determine if the game is over
 *
 * @return true
 * @return false
 */
bool ClassicBrickGrid::allBricksDestroyed() {
    for(auto& brick_vector : m_bricks){
        for(auto& brick : brick_vector){
            if(!brick->isDestroyed() && brick->getType()!=typeBrick::EMPTY){
                return false;
            }
        }
    }
    return true;
}

HexagonalBrickGrid::HexagonalBrickGrid(int rows, int cols, int brickWidth, int brickHeight) : 
        BrickGrid(rows, cols, brickWidth, brickHeight)
{
}
HexagonalBrickGrid::HexagonalBrickGrid(int brickWidth, int brickHeight) : 
        BrickGrid(brickWidth, brickHeight)
{
}

HexagonalBrickGrid::~HexagonalBrickGrid()
{
}
/**
 * @brief initializes the grid from a file
 *
 * @param filename
 * @param initX
 * @param initY
 * @pre filename is a valid file
 * @pre file contains '#' for normal bricks, '*' for double bricks, '@' for
 * triple bricks, and ' ' for empty bricks
 * @post m_bricks contains the grid
 */
void HexagonalBrickGrid::initGridFromFile(const std::string& filename,
                                          const int initX, const int initY) {
  const double padding = 3;
  std::ifstream file(filename);
  if (file.is_open()) {
    
    objectSize size = {m_brickWidth - padding, m_brickHeight - padding};
    std::string line;
    int rowNumber = 0;
    while (std::getline(file, line)) {
      std::vector<std::shared_ptr<Brick>> row;
      for (int colNumber = 0; colNumber < static_cast<int>(line.size());
           colNumber++) {
        char c = line[colNumber];
        double q = colNumber;
        double r = rowNumber;
        std::shared_ptr<Brick> brick = nullptr;
        switch (c) {
          case '#':
            brick =
                std::make_shared<HexagonalBrick>(q, r, size, typeBrick::NORMAL);
            break;
          case '*':
            brick =
                std::make_shared<HexagonalBrick>(q, r, size, typeBrick::DOUBLE);
            break;
          case '@':
            brick =
                std::make_shared<HexagonalBrick>(q, r, size, typeBrick::TRIPLE);
            break;
          case ' ':
            brick =
                std::make_shared<HexagonalBrick>(q, r, size, typeBrick::EMPTY);
            break;
        }
        row.push_back(brick);
      }
      m_bricks.emplace_back(row);
      rowNumber++;
    }
  }
}

/**
 * @brief draws the grid
 *
 * @param renderer
 */
void HexagonalBrickGrid::draw(SDL_Renderer* renderer){
  for (const std::vector<std::shared_ptr<Brick>>& row : m_bricks) {
    for (const std::shared_ptr<Brick>& brick : row) {
      if (brick != nullptr) {
        if (brick->getType() != typeBrick::EMPTY && !brick->isDestroyed()) {
          Color color = {255, 204, 255, 50};
          if (brick->getType() == typeBrick::NORMAL) {
            color = {255, 204, 255, 50};
          } else if (brick->getType() == typeBrick::DOUBLE) {
            color = {255, 51, 153, 250};

          } else if (brick->getType() == typeBrick::TRIPLE) {
            color = {153, 0, 153, 255};
          }
          auto hexagonalBrick = dynamic_cast<HexagonalBrick*>(brick.get());
          if (hexagonalBrick != nullptr) {
            hexagonalBrick->draw(renderer, color);
          }
        }
      }
    }
  }
}


std::vector<std::vector<std::shared_ptr<Brick>>>& HexagonalBrickGrid::getBricks()
{
    return m_bricks;
}

void HexagonalBrickGrid::setRows(int rows) {
    m_rows = rows;
}
/**
 * @brief checks if all bricks are destroyed
 * used to determine if the game is over
 *
 * @return true
 * @return false
 */
bool HexagonalBrickGrid::allBricksDestroyed() {
  for (auto& brick_vector : m_bricks) {
    for (auto& brick : brick_vector) {
      if (!brick->isDestroyed() && brick->getType() != typeBrick::EMPTY) {
        return false;
      }
    }
  }
  return true;
}

void HexagonalBrickGrid::update(){
}