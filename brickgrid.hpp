#ifndef BRICKGRID_H
#define BRICKGRID_H
#include <fstream>
#include <vector>
#include "brick.hpp"
#include "gameObject.hpp"
#include "structs.hpp"

class BrickGrid : public GameObject
{
    private:
        std::vector<std::vector<Brick*>> m_bricks;
        int m_rows;
        int m_cols;
        int m_brickWidth;
        int m_brickHeight;
        SDL_Renderer* m_renderer;

        void setRows(int);
        void setCols(int);
        void setBrickWidth(int);
        void setBrickHeight(int);
    public:
        BrickGrid(position pos, size size, int rows, int cols, int brickWidth, int brickHeight);
        ~BrickGrid();
        SDL_Renderer* getRenderer();

        void initGridFromFile(const std::string& filename);

        void update();
        void render();
        void collidesWith(GameObject* obj);
        void setBrick(int row, int col, typeBrick type);
        void setBrick(int row, int col, Brick* brick);
        
        std::vector<std::vector<Brick*>>& getBricks();
        

        void destroyBrick(int row, int col);
        void destroyBrick(Brick* brick);
        void destroyBrick(int index);
        void destroyBrick(position pos);
        void destroyBrick(int x, int y);
        void destroyBrick(SDL_Rect rect);
        void destroyBrick(SDL_Point point);
        void destroyBrick(SDL_Point point, int radius);
        void destroyBrick(SDL_Point point, int radius, bool filled);
        void destroyBrick(SDL_Point point, int radius, bool filled, int startAngle, int endAngle);
        void destroyBrick(SDL_Point point, int radius, bool filled, int startAngle, int endAngle, SDL_RendererFlip flip);
        void destroyBrick(SDL_Point point, int radius, bool filled, int startAngle, int endAngle, SDL_RendererFlip flip, SDL_Point center);
        void destroyBrick(SDL_Point point, int radius, bool filled, int startAngle, int endAngle, SDL_RendererFlip flip, SDL_Point center, SDL_Rect clip);
        void destroyBrick(SDL_Point point, int radius, bool filled, int startAngle, int endAngle, SDL_RendererFlip flip, SDL_Point center, SDL_Rect clip, double angle);
        void destroyBrick(SDL_Point point, int radius, bool filled, int startAngle, int endAngle, SDL_RendererFlip flip, SDL_Point center, SDL_Rect clip, double angle, SDL_Point centerOfRotation);

};


#endif // BRICKGRID_H