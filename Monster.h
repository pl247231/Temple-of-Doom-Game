#ifndef MONSTER
#define MONSTER

#include "Actor.h"
#include "utilities.h"
#include "Object.h"

//Most functions have short implementations, so they are implemented directly in the h file

class Monster : public Actor
{
public:
	Monster(int x, int y, int hit, int armor, int strength, int dex, Weapon* weap) : Actor(x, y, hit, armor, strength, dex, weap) {}
	virtual char gettype() = 0;
	virtual Object* drop() = 0;
	virtual void heal() {};
};

class Bogeyman : public Monster {
public:
	Bogeyman(int x = 0, int y = 0) : Monster(x, y, randInt(5, 10), 2, randInt(2, 3), randInt(2, 3), new Shortsword()) {}
	virtual char gettype() {
		return 'B';
	}
	virtual std::string getname() {
		return "the Bogeyman";
	}
	virtual Object* drop();
};

class Snakewoman : public Monster {
public:
	Snakewoman(int x = 0, int y = 0) : Monster(x, y, randInt(3, 6), 3, 2, 3, new Fangs()) {}
	virtual char gettype() {
		return 'S';
	}
	virtual std::string getname() {
		return "the Snakewoman";
	}
	virtual Object* drop();
};

class Dragon : public Monster {
public:
	Dragon(int x = 0, int y = 0) : Monster(x, y, randInt(20, 25), 4, 4, 4, new Longsword()) {
		maxhealh = gethit();
	}
	virtual char gettype() {
		return 'D';
	}
	virtual std::string getname() {
		return "the Dragon";
	}
	virtual Object* drop();
	virtual void heal();
private:
	int maxhealh;
};

class Goblin : public Monster {
public:
	Goblin(int x = 0, int y = 0) : Monster(x, y, randInt(15, 20), 1, 3, 1, new Shortsword()) {}
	virtual char gettype() {
		return 'G';
	}
	virtual std::string getname() {
		return "the Goblin";
	}
	virtual Object* drop();
};
#endif // !MONSTER