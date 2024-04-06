#include "brickgrid.hpp"
#include <iostream>
// TODO: prendre les dimensions a partir du fichier
BrickGrid::BrickGrid(size_t rows, size_t cols, size_t brickWidth, size_t brickHeight) : 
        m_rows(rows), m_cols(cols), m_brickWidth{brickWidth}, m_brickHeight(brickHeight)
{
}
BrickGrid::BrickGrid(size_t brickWidth, size_t brickHeight) : 
        m_brickWidth{brickWidth}, m_brickHeight(brickHeight)
{
}

BrickGrid::~BrickGrid()
{
}

void BrickGrid::initGridFromFile(const std::string& filename, const int initX, const int initY)
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
                        
                        position pos = {(colNumber * m_brickWidth)+initX, (rowNumber * m_brickHeight)+initY};
                        std::unique_ptr<Brick> brick = nullptr;
                        switch(c){
                            case '#':{
                                brick=std::make_unique<Brick>(pos, size, typeBrick::NORMAL);
                                row.push_back(std::move(brick));
                                break;
                            }
                            case '*':{
                                brick=std::make_unique<Brick>(pos, size, typeBrick::DOUBLE);
                                row.push_back(std::move(brick));
                                break;
                            }
                            case '@':{
                                brick=std::make_unique<Brick>(pos, size, typeBrick::TRIPLE);
                                row.push_back(std::move(brick));
                                break;
                            }
                            case ' ':
                                brick=std::make_unique<Brick>(pos, size, typeBrick::EMPTY);
                                row.push_back(std::move(brick));
                                break;
                        }
                        
                    }
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

void BrickGrid::update(){
    // for (auto& row : m_bricks) {
    //     for (auto& brick : row) {
    //         if (brick != nullptr) {
    //             brick->update();
    //         }
    //     }
    // }
}