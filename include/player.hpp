#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    int score;
    int level;
    int lives;
public:
    Player();
    ~Player();
    void updateScore(int);
    void updateLevel(int);
    void updateLives(int);
};



#endif // PLAYER_H