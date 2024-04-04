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
            const size_t padding = 5;
            std::ifstream file(filename);
            if(file.is_open())
            {
                objectSize size = {m_brickWidth - padding, m_brickHeight - padding};
                std::string line;
                size_t rowNumber = 0;
                while(std::getline(file, line))
                {
                    std::vector<std::unique_ptr<Brick>> row;
                    for(size_t colNumber = 0; colNumber < line.size(); colNumber++){
                        char c = line[colNumber];
                        std::cout<<"c: "<<c<<std::endl;
                        position pos = {static_cast<size_t>(colNumber * m_brickWidth), static_cast<size_t>(rowNumber * m_brickHeight)};
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
                            default:
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