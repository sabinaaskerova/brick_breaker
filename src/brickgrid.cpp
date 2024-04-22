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
      // m_bricks.push_back(row);
      m_bricks.emplace_back(row);
      rowNumber++;
    }
  }
}

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

void ClassicBrickGrid::printAllBricks() const {
    for (const auto& row : m_bricks) {
        for (const auto& brick : row) {
            if (brick != nullptr) {
                brick->printProperties();
            }
        }
        std::cout << std::endl;
    }
}


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
void HexagonalBrickGrid::initGridFromFile(const std::string& filename, const int initX, const int initY){
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
            (colNumber * m_brickWidth) +
                (rowNumber % 2 == 0 ? 0 : m_brickWidth / 2) +
                static_cast<double>(initX),
            (rowNumber * m_brickHeight * 3 / 4) + static_cast<double>(initY)};
        std::shared_ptr<Brick> brick = nullptr;
        switch (c) {
          case '#': {
            brick = std::make_shared<HexagonalBrick>(pos.x, pos.y, size,
                                                     typeBrick::NORMAL);
            row.push_back(brick);
            break;
          }
          case '*': {
            brick = std::make_shared<HexagonalBrick>(pos.x, pos.y, size,
                                                     typeBrick::DOUBLE);
            row.push_back(brick);
            break;
          }
          case '@': {
            brick = std::make_shared<HexagonalBrick>(pos.x, pos.y, size,
                                                     typeBrick::TRIPLE);
            row.push_back(brick);
            break;
          }
          case ' ':
            brick = std::make_shared<HexagonalBrick>(pos.x, pos.y, size,
                                                     typeBrick::EMPTY);
            row.push_back(brick);
            break;
        }
      }
      m_bricks.emplace_back(row);
      rowNumber++;
    }
  }
    }

void HexagonalBrickGrid::draw(SDL_Renderer* renderer){
  for (const std::vector<std::shared_ptr<Brick>>& row : m_bricks) {
    for (const std::shared_ptr<Brick>& brick : row) {
      if (brick != nullptr) {
        if (brick->getType() != typeBrick::EMPTY && !brick->isDestroyed()) {
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


std::vector<std::vector<std::shared_ptr<Brick>>>& HexagonalBrickGrid::getBricks()
{
    return m_bricks;
}

void HexagonalBrickGrid::setRows(int rows) {
    m_rows = rows;
}

void HexagonalBrickGrid::printAllBricks() const {
  for (const auto& row : m_bricks) {
    for (const auto& brick : row) {
      if (brick != nullptr) {
        brick->printProperties();
      }
    }
    std::cout << std::endl;
  }
}

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