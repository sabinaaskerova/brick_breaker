#include "brickgrid.hpp"
#include <iostream>
// TODO: prendre les dimensions a partir du fichier
BrickGrid::BrickGrid(size_t rows, size_t cols, size_t brickWidth, size_t brickHeight) : 
        m_rows(rows), m_cols(cols), m_brickWidth{brickWidth}, m_brickHeight(brickHeight)
{
}

BrickGrid::~BrickGrid()
{
}

void BrickGrid::initGridFromFile(const std::string& filename)
        {
            const int padding = 5;
            std::ifstream file(filename);
            if(file.is_open())
            {
                objectSize size = {m_brickWidth - padding, m_brickHeight - padding};
                std::string line;
                int rowNumber = 0;
                while(std::getline(file, line))
                {
                    
                    std::vector<std::unique_ptr<Brick>> row;
                    for(int colNumber = 0; colNumber < static_cast<int>(line.size()); colNumber++){
                        char c = line[colNumber];
                        
                        position pos = {(colNumber * m_brickWidth), (rowNumber * m_brickHeight)};
                        std::unique_ptr<Brick> brick = nullptr;
                        switch(c){
                            case '#':{
                                brick=std::make_unique<Brick>(pos, size, typeBrick::NORMAL);
                                row.push_back(std::move(brick));
                                std::cout << NORMAL ;
                                break;
                            }
                            case '*':{
                                brick=std::make_unique<Brick>(pos, size, typeBrick::DOUBLE);
                                row.push_back(std::move(brick));
                                std::cout << DOUBLE;
                                break;
                            }
                            case '@':{
                                brick=std::make_unique<Brick>(pos, size, typeBrick::TRIPLE);
                                row.push_back(std::move(brick));
                                std::cout << TRIPLE;
                                break;
                            }
                            case ' ':
                                brick=std::make_unique<Brick>(pos, size, typeBrick::EMPTY);
                                row.push_back(std::move(brick));
                                std::cout << EMPTY;
                                break;
                            
                            // default:
                            //     break;
                        }
                        
                    }
                    std::cout << std::endl;
                    m_bricks.push_back(std::move(row));
                    rowNumber++;
                }
            }
        }

std::vector<std::vector<std::unique_ptr<Brick>>>& BrickGrid::getBricks()
{
    return m_bricks;
}

void BrickGrid::setRows(int rows) {
    m_rows = rows;
}

void BrickGrid::printAllBricks() const {
    for (const auto& row : m_bricks) {
        for (const auto& brick : row) {
            if (brick != nullptr) {
                brick->printProperties();
            }
        }
        std::cout << std::endl;
    }
}