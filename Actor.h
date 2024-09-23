#ifndef ACTOR
#define ACTOR

#include<cmath>
#include "Object.h"
#include "utilities.h"

class Actor
{
public:
	Actor(int x, int y, int hit, int armor, int strength, int dex, Weapon* weap);
	virtual ~Actor();
	//getters
	int getx() {
		return m_x;
	}
	int gety() {
		return m_y;
	}
	int gethit() {
		return hitpoints;
	}
	int getarmor() {
		return armorpoints;
	}
	int getstrength() {
		return strengthpoints;
	}
	int getdex() {
		return dexteritypoints;
	}
	virtual std::string getname() = 0;
	Weapon* getweapon() {
		return currweapon;
	}
	//mutators
	void changehit(int amt) {
		hitpoints += amt;
	}
	void incrementhit() {
		hitpoints++;
	}
	void sethealth(int health) {
		hitpoints = health;
	}
	void setstrength(int strength) {
		strengthpoints = strength;
	}
	void setarmor(int armor) {
		armorpoints = armor;
	}
	void setdex(int dex) {
		dexteritypoints = dex;
	}
	virtual void heal() = 0;
	void changesleep(int time);
	bool decrementsleep();
	void moveleft() {
		m_x--;
	}
	void moveright() {
		m_x++;
	}
	void moveup() {
		m_y--;
	}
	void movedown() {
		m_y++;
	}
	void setx(int x) {
		m_x = x;
	}
	void sety(int y) {
		m_y = y;
	}
	void clearweapon() {
		currweapon = nullptr;
	}
	void setweapon(Weapon* weapon) {
		currweapon = weapon;
	}
	std::string hit(Actor* target);
	int dist(int x, int y) {
		return abs(m_x - x) + abs(m_y - y);
	}

private:
	int m_x, m_y;
	int hitpoints, armorpoints, strengthpoints, dexteritypoints;
	int sleeptime;
	Weapon* currweapon;
};


#endif // !ACTOR
