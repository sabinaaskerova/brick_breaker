#ifndef BRICKGRID_H
#define BRICKGRID_H
#include <fstream>
#include <vector>
#include "brick.hpp"
#include "gameObject.hpp"
#include "structs.hpp"
#include <memory>

class BrickGrid
{
    private:
        std::vector<std::vector<std::unique_ptr<Brick>>> m_bricks;
        int m_rows;
        int m_cols;
        int m_brickWidth;
        int m_brickHeight;
        SDL_Renderer* m_renderer;

        void setRows(int);
        void setCols(int);
    public:
        BrickGrid(size_t rows, size_t cols, size_t brickWidth, size_t brickHeight);
        ~BrickGrid();
        SDL_Renderer* getRenderer();

        void initGridFromFile(const std::string& filename);

        void update();
        void render();
        void collidesWith(GameObject* obj);
        void setBrick(int row, int col, typeBrick type);
        void setBrick(int row, int col, Brick* brick);

        void setBrickWidth(int x);
        void setBrickHeight(int y);
        std::vector<std::vector<std::unique_ptr<Brick>>>& getBricks();
        

        void destroyBrick(int row, int col);

        void printAllBricks() const;

};


#endif // BRICKGRID_H