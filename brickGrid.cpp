#include "brickgrid.hpp"

// TODO: prendre les dimensions a partir du fichier
BrickGrid::BrickGrid(position pos, size size, int rows, int cols, int brickWidth, int brickHeight)
{
    // setPos(pos);
    // setSize(size);
    setRows(rows);
    setCols(cols);
    setBrickWidth(brickWidth);
    setBrickHeight(brickHeight);
}

BrickGrid::~BrickGrid()
{
    for(auto& row : m_bricks)
    {
        for(auto& brick : row)
        {
            delete &brick;
        }
    }
}

void BrickGrid::initGridFromFile(const std::string& filename)
        {
            std::ifstream file(filename);
            if(file.is_open())
            {
                size size = {m_brickWidth, m_brickHeight};
                std::string line;
                int rowNumber = 0;
                while(std::getline(file, line))
                {
                    std::vector<Brick*> row;
                    for(int colNumber = 0; colNumber < line.size(); colNumber++){
                        char c = line[colNumber];
                        position pos = {colNumber * m_brickWidth, rowNumber * m_brickHeight};
                        switch(c){
                            case '#':{
                                Brick* brick=new Brick(pos, size, typeBrick::NORMAL);
                                row.push_back(brick);
                                break;
                            }
                            case '*':{
                                Brick* brick=new Brick(pos, size, typeBrick::DOUBLE);
                                row.push_back(brick);
                                break;
                            }
                            case '@':{
                                Brick* brick=new Brick(pos, size, typeBrick::TRIPLE);
                                row.push_back(brick);
                                break;
                            }
                            case ' ':
                                row.push_back(nullptr);
                                break;
                            defaukt:
                                row.push_back(nullptr);
                                break;
                        }
                    }
                    m_bricks.push_back(row);
                    rowNumber++;
                }
            }
        }

std::vector<std::vector<Brick*>> &BrickGrid::getBricks()
{
    return m_bricks;
}