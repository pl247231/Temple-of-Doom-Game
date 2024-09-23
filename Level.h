#ifndef LEVEL
#define LEVEL

#include<iostream>
#include<vector>
#include<utility>
#include<cmath>
#include<algorithm>

#include"Player.h"
#include"Monster.h"
#include"utilities.h"
#include"Object.h"

//helper functions
int xdisttoclosest(std::vector<std::pair<int, int>> centers, std::pair<int, int> point);
int ydisttoclosest(std::vector<std::pair<int, int>> centers, std::pair<int, int> point);
std::pair<int, int> closestconnected(std::vector<std::pair<int, int>> centers, std::vector<bool> connected, std::pair<int, int> point);

class Level
{
public:
    Level(Player* player, int levelnum, int goblinsmell);
    ~Level();
    bool pickup();
    void showinventory();
    void placeactor(Actor* act);
    void randaddmonster(Monster* monst);
    void placeobject(Object* obj);
    void randaddobject(Object* obj);
    bool inside(int x, int y);
    bool actorallowed(int x, int y, Actor* actor);
    bool objectallowed(int x, int y);
    int indexmonstat(int x, int y);
    int indexobjectat(int x, int y);
    bool movedumb(Monster* monst);
    void gendists(int x, int y, int dist, Monster* monst);
    bool movegoblin(Monster* monst);
    void monstattack(Monster* monst);
    void monstersturn();
    void playerattack(int x, int y);
    int turn(char ch);
    void display();

private:
    char grid[70][18];
    int disttoplayer[70][18];
    //need pointers to monster and object for polymorphism, even though they belong solely to level
    std::vector<Monster*> m_monsters;
    std::vector<Object*> m_objects;
    Player* m_player;
    //pointer to stair to reuse functions written for object
    Stair* m_stair;
    int m_levelnum;
    int smelldist;
    std::string message;
};


#endif // ! LEVEL


