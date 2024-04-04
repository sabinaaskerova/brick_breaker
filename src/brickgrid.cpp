#include "brickgrid.hpp"
#include <iostream>
// TODO: prendre les dimensions a partir du fichier
BrickGrid::BrickGrid(int rows, int cols, int brickWidth, int brickHeight) : 
        m_rows(rows), m_cols(cols), m_brickWidth{brickWidth}, m_brickHeight(brickHeight)
{
    m_bricks.reserve(rows);
    for(int i = 0; i < rows; i++)
    {
        std::vector<Brick> row;
        row.reserve(cols);
        for(int j = 0; j < cols; j++)
        {
            position pos = {static_cast<size_t>(j * brickWidth), static_cast<size_t>(i * brickHeight)};
            objectSize size = {brickWidth, brickHeight};
            row.push_back(Brick(pos, size, typeBrick::NORMAL));
        }
        m_bricks.push_back(row);
    }
}

BrickGrid::~BrickGrid()
{
    // for(std::vector<Brick>& row : m_bricks)
    // {
    //     for(Brick& brick : row)
    //     {
    //         delete &brick; // delete brick pointer itself
            
    //     }
    // }
}

void BrickGrid::initGridFromFile(const std::string& filename)
        {
            std::ifstream file(filename);
            if(file.is_open())
            {
                objectSize size = {m_brickWidth, m_brickHeight};
                std::string line;
                size_t rowNumber = 0;
                while(std::getline(file, line))
                {
                    std::vector<Brick> row;
                    for(size_t colNumber = 0; colNumber < line.size(); colNumber++){
                        char c = line[colNumber];
                        position pos = {static_cast<size_t>(colNumber * m_brickWidth), static_cast<size_t>(rowNumber * m_brickHeight)};
                        // Brick* brick = nullptr;
                        switch(c){
                            case '#':{
                                row.push_back(Brick(pos, size, typeBrick::NORMAL));
                                break;
                            }
                            case '*':{
                                row.push_back(Brick(pos, size, typeBrick::DOUBLE));
                                break;
                            }
                            case '@':{
                                row.push_back(Brick(pos, size, typeBrick::TRIPLE));
                                break;
                            }
                            case ' ':
                                row.push_back(Brick(pos, size, typeBrick::EMPTY));
                                break;
                            default:
                                row.push_back(Brick(pos, size, typeBrick::EMPTY));
                                break;
                        }
                    }
                    m_bricks.push_back(row);
                    rowNumber++;
                }
            }
        }

std::vector<std::vector<Brick>> &BrickGrid::getBricks()
{
    return m_bricks;
}

void BrickGrid::setRows(int rows) {

}