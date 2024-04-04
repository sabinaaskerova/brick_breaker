#ifndef BRICKGRID_H
#define BRICKGRID_H
#include <fstream>
#include <vector>
#include "brick.hpp"
#include "gameObject.hpp"
#include "structs.hpp"

class BrickGrid
{
    private:
        std::vector<std::vector<Brick>> m_bricks;
        int m_rows;
        int m_cols;
        int m_brickWidth;
        int m_brickHeight;
        SDL_Renderer* m_renderer;

        void setRows(int);
        void setCols(int);
        // void setBrickWidth(int);
        // void setBrickHeight(int);
    public:
        BrickGrid(int rows, int cols, int brickWidth, int brickHeight);
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
        std::vector<std::vector<Brick>>& getBricks();
        

        void destroyBrick(int row, int col);
};


#endif // BRICKGRID_H