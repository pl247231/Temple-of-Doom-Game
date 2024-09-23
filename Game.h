// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.

#include "Level.h"
#include "Player.h"
#include "utilities.h"
class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
private:
    Player m_player;
    Level* m_currlevel;
    int m_levelnum;
    int m_goblinsmell;
};

#endif // GAME_INCLUDED
