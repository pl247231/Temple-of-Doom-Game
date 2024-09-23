#include "Game.h"
#include "Level.h"
#include "utilities.h"
#include <iostream>

using namespace std;

Game::Game(int goblinSmellDistance) : m_player(1, 1)
{
    //set member variables
    m_levelnum = 0;
    m_currlevel = new Level(&m_player, 0, goblinSmellDistance);
    m_goblinsmell = goblinSmellDistance;
}
Game::~Game() {
    delete m_currlevel;
}
void Game::play()
{
    while (true) {
        clearScreen();
        m_currlevel->display();
        char ch = getCharacter();
        //quit on q
        if (ch == 'q') {
            break;
        }
        int result = m_currlevel->turn(ch);
        //end of game
        if (result == 2) {
            clearScreen();
            m_currlevel->display();
            while (true) {
                ch = getCharacter();
                if (ch == 'q') {
                    break;
                }
            }
            break;
        }
        //moving to new level
        else if (result == 1) {
            m_levelnum++;
            delete m_currlevel;
            m_currlevel = new Level(&m_player, m_levelnum, m_goblinsmell);
        }
    }
}
