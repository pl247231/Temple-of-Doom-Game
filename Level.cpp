#include "Level.h"

using namespace std;

Level::Level(Player* player, int levelnum, int goblinsmell) {
    //fill in entire grid with walls
    for (int i = 0; i < 70; i++) {
        grid[i][0] = '#';
        grid[i][17] = '#';
    }
    for (int i = 0; i < 18; i++) {
        grid[0][i] = '#';
        grid[69][i] = '#';
    }
    for (int i = 1; i < 17; i++) {
        for (int j = 1; j < 69; j++) {
            grid[j][i] = '#';
        }
    }
    int roomnum = randInt(4, 6);
    vector<pair<int, int>> roomcenters;
    vector<bool> connected;

    //choose first room center, but don't yet fill in room
    roomcenters.push_back(make_pair(randInt(1, 68), randInt(1, 16)));
    connected.push_back(true);

    //choose roomnum - 1 more room centers and create the rooms
    for (int i = 0; i < roomnum - 1; i++) {
        while (true) {
            //randomly choose a room center
            int x = randInt(1, 68);
            int y = randInt(1, 16);
            //find x and y distance to rooms that are close enough to potentially intersect
            int distx = xdisttoclosest(roomcenters, make_pair(x, y));
            int disty = ydisttoclosest(roomcenters, make_pair(x, y));
            //if distances are valid (far enough to guarantee non intersection but close enough to not have too long hallways)
            if (distx > 11 && distx < 40 && disty > 7) {
                //add room center to vector keeping track of room centers
                roomcenters.push_back(make_pair(x, y));
                connected.push_back(false);
                //find bounds for room width and height
                int maxwidth = min(distx / 2, 5);
                int maxheight = min(disty / 2, 3);
                //generate width and height of the room
                int width = randInt(4, maxwidth);
                int height = randInt(2, maxheight);
                //fill in grid positions with spaces
                for (int a = x - width; a <= x + width; a++) {
                    for (int b = y - height; b <= y + height; b++) {
                        if (a > 0 && a < 69 && b > 0 && b < 17) {
                            grid[a][b] = ' ';
                        }
                    }
                }
                break;
            }
        }
    }
    //fill in first room
    int x = roomcenters[0].first;
    int y = roomcenters[0].second;
    //erase room from roomcenters so that correct distances are returned instead of 0
    roomcenters.erase(roomcenters.begin());
    int distx = xdisttoclosest(roomcenters, make_pair(x, y));
    int disty = ydisttoclosest(roomcenters, make_pair(x, y));
    //add room back
    roomcenters.insert(roomcenters.begin(), make_pair(x, y));
    //find bounds of width and height
    int maxwidth = min(distx / 2, 5);
    int maxheight = min(disty / 2, 3);
    //randomly generate width and height
    int width = randInt(3, maxwidth);
    int height = randInt(1, maxheight);
    //fill in the room with spaces
    for (int a = x - width; a <= x + width; a++) {
        for (int b = y - height; b <= y + height; b++) {
            if (a > 0 && a < 69 && b > 0 && b < 17) {
                grid[a][b] = ' ';
            }
        }
    }
    //connect each unconnected room to the closest connected room
    for (int i = 0; i < roomnum; i++) {
        pair<int, int> currroom = roomcenters[i];
        pair<int, int> closest = closestconnected(roomcenters, connected, currroom);
        //determine what position that is on the left and right
        pair<int, int> left;
        pair<int, int> right;
        if (currroom.first < closest.first) {
            left = currroom;
            right = closest;
        }
        else {
            left = closest;
            right = currroom;
        }
        //right center is higher
        if (right.second < left.second) {
            //generate horizontal portion of corridor
            for (int j = left.first; j <= right.first; j++) {
                grid[j][right.second] = ' ';
            }
            //generate vertical portion of corridor
            for (int j = right.second; j <= left.second; j++) {
                grid[left.first][j] = ' ';
            }
        }
        //left center is higher
        else {
            //generate horizontal portion of corridor
            for (int j = left.first; j <= right.first; j++) {
                grid[j][left.second] = ' ';
            }
            //generate vertical portion of corridor
            for (int j = left.second; j <= right.second; j++) {
                grid[right.first][j] = ' ';
            }
        }
        //mark room as connected
        connected[i] = true;
    }

    //initialize member variables
    smelldist = goblinsmell;
    m_player = player;
    m_levelnum = levelnum;

    //randomly place player
    placeactor(m_player);

    //place stair/idol
    if (m_levelnum < 4) {
        m_stair = new Stair();
        placeobject(m_stair);
    }
    else {
        m_stair = nullptr;
        randaddobject(new Idol());
    }
    //randomly generate number of monsters and objects
    int nummonsters = randInt(2, 5 * (m_levelnum + 1) + 1);
    int numobjects = randInt(2, 3);
    int numscroll = randInt(0, 2);
    int numweapon = numobjects - numscroll;
    //add weapons
    for (int i = 0; i < numweapon; i++) {
        switch (randInt(1, 3)) {
        case 1:
            //mace
            randaddobject(new Mace());
            break;
        case 2:
            //short sword
            randaddobject(new Shortsword());
            break;
        case 3:
            //long sword
            randaddobject(new Longsword());
            break;
        }
    }
    //add scrolls
    for (int i = 0; i < numscroll; i++) {
        switch (randInt(1, 4)) {
        case 1:
            //strength scroll
            randaddobject(new Scrollstrength());
            break;
        case 2:
            //armor scroll
            randaddobject(new Scrollarmor());
            break;
        case 3:
            //health scroll
            randaddobject(new Scrollhealth());
            break;
        case 4:
            //dex scroll
            randaddobject(new Scrolldex());
            break;
        }
    }
    //add monsters according to level number
    for (int i = 0; i < nummonsters; i++) {
        if (m_levelnum < 2) {
            int type = randInt(1, 2);
            if (type == 1) {
                randaddmonster(new Snakewoman());
            }
            else {
                randaddmonster(new Goblin());
            }
        }
        else if (m_levelnum == 2) {
            int type = randInt(1, 3);
            if (type == 1) {
                randaddmonster(new Snakewoman());
            }
            else if (type == 2) {
                randaddmonster(new Goblin());
            }
            else {
                randaddmonster(new Bogeyman());
            }
        }
        else {
            int type = randInt(1, 4);
            if (type == 1) {
                randaddmonster(new Snakewoman());
            }
            else if (type == 2) {
                randaddmonster(new Goblin());
            }
            else if (type == 3) {
                randaddmonster(new Bogeyman());
            }
            else {
                randaddmonster(new Dragon());
            }
        }
    }
}
Level::~Level()
{
    //delete all objects and monsters bound to level
    for (Object* obj : m_objects) {
        delete obj;
    }
    for (Monster* monst : m_monsters) {
        delete monst;
    }
    //delete stair bound to level
    delete m_stair;
}
int xdisttoclosest(vector<pair<int, int>> centers, pair<int, int> point) {
    //find closest horizontal distance to another room that has roughly the same y value
    int bestdist = 1000;
    for (int i = 0; i < centers.size(); i++) {
        int dist = abs(centers[i].first - point.first);
        if (dist < bestdist && abs(centers[i].second - point.second) <= 18 / centers.size()) {
            bestdist = dist;
        }
    }
    return bestdist;
}
int ydisttoclosest(vector<pair<int, int>> centers, pair<int, int> point) {
    //find closest vertical distance to another room that has roughly the same x value
    int bestdist = 1000;
    for (int i = 0; i < centers.size(); i++) {
        int dist = abs(centers[i].second - point.second);
        if (dist < bestdist && abs(centers[i].first - point.first) <= 80 / centers.size()) {
            bestdist = dist;
        }
    }
    return bestdist;
}

pair<int, int> closestconnected(vector<pair<int, int>> centers, vector<bool> connected, pair<int, int> point) {
    //find closest connected center
    pair<int, int> closest = centers[0];
    int bestdist = 100000;
    for (int i = 0; i < centers.size(); i++) {
        int dist = abs(centers[i].first - point.first) + abs(centers[i].second - point.second);
        if (connected[i] && dist < bestdist) {
            bestdist = dist;
            closest = centers[i];
        }
    }
    return closest;
}
bool Level::pickup() {
    //return true if picked up idol, false otherwise
    for (int i = 0; i < m_objects.size(); i++) {
        //find object player is standing on
        Object* obj = m_objects[i];
        if (obj->getx() == m_player->getx() && obj->gety() == m_player->gety()) {
            //if inventory is full
            if (m_player->getinventory().size() == 26) {
                message += "Your knapsack is full; you can't pick that up.\n";
                return false;
            }
            //determine if object is a scroll
            bool isscroll = obj->getname().substr(0, 6) == "scroll";
            //add object to inventory
            m_player->addtoinventory(obj);
            //remove object from list of objects to display
            m_objects.erase(m_objects.begin() + i);
            //add correct text to later output
            if (isscroll) {
                message += "You pick up a scroll called " + obj->getname() + "\n";
                return false;
            }
            else {
                message += "You pick up " + obj->getname() + "\n";
                if (obj->getname() == "the golden idol") {
                    message += "Congratulations, you won!\nPress q to exit game\n";
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}
void Level::showinventory() {
    clearScreen();
    cout << "Inventory:" << endl;
    char ch = 'a';
    for (Object* obj : (m_player->getinventory())) {
        //output letters and names of objects in inventory
        if (obj->getname().substr(0, 6) == "scroll") {
            cout << " " << ch << ". " << "A scroll called " + obj->getname() << endl;
        }
        else {
            cout << " " << ch << ". " << obj->getname() << endl;
        }
        ch++;
    }
}
void Level::placeactor(Actor* act) {
    //generate random positions until it finds one player is allowed to be on
    while (true) {
        int x = randInt(0, 69);
        int y = randInt(0, 17);
        if (actorallowed(x, y, act)) {
            act->setx(x);
            act->sety(y);
            return;
        }
    }
}
void Level::randaddmonster(Monster* monst) {
    //randomly place monster, then add it to vector of monsters
    placeactor(monst);
    m_monsters.push_back(monst);
}
void Level::placeobject(Object* obj) {
    //generate random positions until it finds one object is allowed to be on
    while (true) {
        int x = randInt(0, 69);
        int y = randInt(0, 17);
        if (objectallowed(x, y)) {
            obj->setx(x);
            obj->sety(y);
            return;
        }
    }
}
void Level::randaddobject(Object* obj) {
    //randomly place object, then add it to vector of objects
    placeobject(obj);
    m_objects.push_back(obj);
}
bool Level::inside(int x, int y) {
    //check if point is inside the grid
    if (x > 69 || x < 0 || y > 17 || y < 0) {
        return false;
    }
    return true;
}
bool Level::actorallowed(int x, int y, Actor* actor) {
    //check if actor is allowed to be on a specific position
    if (!inside(x, y) || grid[x][y] == '#') {
        return false;
    }
    for (Monster* monst : m_monsters) {
        if (monst->getx() == x && monst->gety() == y && monst != actor) {
            return false;
        }
    }
    if (m_player->getx() == x && m_player->gety() == y && m_player != actor) {
        return false;
    }
    return true;
}
bool Level::objectallowed(int x, int y) {
    //check if object is allowed to be on a specific position
    if (!inside(x, y) || grid[x][y] == '#') {
        return false;
    }
    if (m_levelnum < 4 && m_stair->getx() == x && m_stair->gety() == y) {
        return false;
    }
    for (Object* object : m_objects) {
        if (object->getx() == x && object->gety() == y) {
            return false;
        }
    }
    return true;
}
int Level::indexmonstat(int x, int y) {
    //find index of monster at a specific coordinate
    for (int i = 0; i < m_monsters.size(); i++) {
        Monster* monst = m_monsters[i];
        if (monst->getx() == x && monst->gety() == y) {
            return i;
        }
    }
    return -1;
}
int Level::indexobjectat(int x, int y) {
    //find index of object at a specific coordinate
    for (int i = 0; i < m_objects.size(); i++) {
        Object* object = m_objects[i];
        if (object->getx() == x && object->gety() == y) {
            return i;
        }
    }
    return -1;
}
bool Level::movedumb(Monster* monst) {
    //move a dumb monster (Snakewoman or Bogeyman)
    //return false if can attack player instead, true otherwise
    int currx = monst->getx();
    int curry = monst->gety();
    int disttoplayer = m_player->dist(currx, curry);
    //determine smell range
    int range;
    if (monst->gettype() == 'B') {
        range = 5;
    }
    else {
        range = 3;
    }
    //right next to player, can attack
    if (disttoplayer == 1) {
        return false;
    }
    //not directly next to player but stil within range
    else if (disttoplayer <= range) {
        //if a move makes it closer to the player, move in that direction
        if (actorallowed(currx + 1, curry, monst) && m_player->dist(currx + 1, curry) < disttoplayer) {
            monst->moveright();
        }
        else if (actorallowed(currx - 1, curry, monst) && m_player->dist(currx - 1, curry) < disttoplayer) {
            monst->moveleft();
        }
        else if (actorallowed(currx, curry + 1, monst) && m_player->dist(currx, curry + 1) < disttoplayer) {
            monst->movedown();
        }
        else if (actorallowed(currx, curry - 1, monst) && m_player->dist(currx, curry - 1) < disttoplayer) {
            monst->moveup();
        }
    }
    //out of range
    return true;
}
void Level::gendists(int x, int y, int dist, Monster* monst) {
    //helper function used to fill grid of distances to player for goblin pathfinding
    int dx[] = { 1, -1, 0, 0 };
    int dy[] = { 0, 0, 1, -1 };
    if (dist < smelldist) {
        for (int i = 0; i < 4; i++) {
            int newx = x + dx[i];
            int newy = y + dy[i];
            //if current search provides a shorter path to a coordinate
            if (actorallowed(newx, newy, monst) && disttoplayer[newx][newy] > dist + 1) {
                //search neightboring coordinates with this new smaller distance
                gendists(newx, newy, dist + 1, monst);
            }
        }
    }
    //set distance to player for this coordinate
    disttoplayer[x][y] = dist;
}
bool Level::movegoblin(Monster* monst) {
    //return false if can attack, true otherwise
    int gobx = monst->getx();
    int goby = monst->gety();
    if (m_player->dist(gobx, goby) == 1) {
        return false;
    }
    for (int i = 0; i < 70; i++) {
        for (int j = 0; j < 18; j++) {
            //initialize distances to a large number
            disttoplayer[i][j] = 100000;
        }
    }
    //fill in grid with distances to player
    gendists(m_player->getx(), m_player->gety(), 0, monst);

    int currdist = disttoplayer[gobx][goby];
    int dx[] = { 1, -1, 0, 0 };
    int dy[] = { 0, 0, 1, -1 };
    for (int i = 0; i < 4; i++) {
        //if a valid goblin move decreases its distance to player, take it
        if (disttoplayer[gobx + dx[i]][goby + dy[i]] < currdist) {
            switch (i) {
            case 0:
                monst->moveright();
                return true;
            case 1:
                monst->moveleft();
                return true;
            case 2:
                monst->movedown();
                return true;
            case 3:
                monst->moveup();
                return true;
            }
        }
    }
    return true;
}
void Level::monstattack(Monster* monst) {
    //attack player and return attack string
    message += monst->hit(m_player) + '\n';
}
void Level::monstersturn() {
    for (Monster* monst : m_monsters) {
        monst->heal();
        if (monst->decrementsleep()) {
            //if sleeping dont act
            continue;
        }
        char type = monst->gettype();
        if (type == 'B' || type == 'S') {
            //Bogeyman and Snakewoman
            if (!movedumb(monst)) {
                //if in range attack, otherwise move if valid
                monstattack(monst);
            }
        }
        else if (type == 'D') {
            //Dragon
            if (m_player->dist(monst->getx(), monst->gety()) == 1) {
                monstattack(monst);
            }
        }
        else {
            if (!movegoblin(monst)) {
                //if in range attack, otherwise move if valid
                monstattack(monst);
            }
        }
    }
}
void Level::playerattack(int x, int y) {
    int monstindex = indexmonstat(x, y);
    //if there is a monster at the position
    if (monstindex != -1) {
        Monster* monst = m_monsters[monstindex];
        //hit monster and return attack string
        message += m_player->hit(monst) + '\n';
        //if monster dies, deal with drops and deletion of monster
        if (monst->gethit() <= 0) {
            Object* drop = monst->drop();
            if (drop != nullptr && indexobjectat(monst->getx(), monst->gety()) == -1) {
                m_objects.push_back(drop);
            }
            delete monst;
            m_monsters.erase(m_monsters.begin() + monstindex);
        }
    }
}
int Level::turn(char ch) {
    //returns 0 if normal play, 1 if go down stairs, 2 if player died or got idol
    //clear message
    message = "";
    char c;
    string update;
    //in normal play return 0
    int playerx = m_player->getx();
    int playery = m_player->gety();
    //regnerate health
    m_player->heal();
    //if player not sleeping, can act
    if (!(m_player->decrementsleep())) {
        switch (ch) {
        case ARROW_DOWN:
            if (actorallowed(playerx, playery + 1, m_player)) {
                m_player->movedown();
            }
            else {
                playerattack(playerx, playery + 1);
            }
            break;
        case ARROW_LEFT:
            if (actorallowed(playerx - 1, playery, m_player)) {
                m_player->moveleft();
            }
            else {
                playerattack(playerx - 1, playery);
            }
            break;
        case ARROW_UP:
            if (actorallowed(playerx, playery - 1, m_player)) {
                m_player->moveup();
            }
            else {
                playerattack(playerx, playery - 1);
            }
            break;
        case ARROW_RIGHT:
            if (actorallowed(playerx + 1, playery, m_player)) {
                m_player->moveright();
            }
            else {
                playerattack(playerx + 1, playery);
            }
            break;
        case '>':
            //on stair
            if (m_levelnum < 4 && playerx == m_stair->getx() && playery == m_stair->gety()) {
                return 1;
            }
            break;
        case 'c':
            //cheat mode
            m_player->sethealth(50);
            m_player->setstrength(9);
            break;
        case 'g':
            //if the player picks up the idol return 2
            if (pickup()) {
                return 2;
            }
            break;
        case 'i':
            showinventory();
            c = getCharacter();
            break;
        case 'w':
            //trying to equip a weapon
            showinventory();
            c = getCharacter();
            update = m_player->equip(c - 'a');
            if (update != "") {
                message += update + '\n';
            }
            break;
        case 'r':
            //trying to read a scroll
            showinventory();
            c = getCharacter();
            update = m_player->read(c - 'a');
            if (update != "") {
                message += update + '\n';
                //teleport scroll, randomly place player
                if (update.substr(update.length() - 5, 5) == "time.") {
                    placeactor(m_player);
                }
            }
            break;
        }
    }
    monstersturn();
    //if player dies return 2
    if (m_player->gethit() <= 0) {
        message += "Press q to exit game\n";
        return 2;
    }
    return 0;

}
void Level::display() {
    //display locations of objects
    for (Object* obj : m_objects) {
        if (obj->getname().substr(0, 6) == "scroll") {
            grid[obj->getx()][obj->gety()] = '?';
        }
        else if (obj->getname() == "the golden idol") {
            grid[obj->getx()][obj->gety()] = '&';
        }
        else {
            grid[obj->getx()][obj->gety()] = ')';
        }
    }

    //place stair if level 1-4
    if (m_levelnum < 4) {
        grid[m_stair->getx()][m_stair->gety()] = '>';
    }

    //place player character
    grid[m_player->getx()][m_player->gety()] = '@';

    //place monster characters
    for (Monster* monst : m_monsters) {
        grid[monst->getx()][monst->gety()] = monst->gettype();
    }
    //display grid
    for (int j = 0; j < 18; j++) {
        for (int i = 0; i < 70; i++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    //display stats and message of all interactions
    cout << "Level: " << m_levelnum << ", Hit points: " << m_player->gethit() << ", Armor: " << m_player->getarmor() << ", Strength: " << m_player->getstrength() << ", Dexterity: " << m_player->getdex() << "\n\n";
    cout << message;

    //clean up actors positions for next move
    grid[m_player->getx()][m_player->gety()] = ' ';
    for (Monster* monst : m_monsters) {
        grid[monst->getx()][monst->gety()] = ' ';
    }
}








