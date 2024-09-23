#include "Actor.h"

Actor::Actor(int x, int y, int hit, int armor, int strength, int dex, Weapon* weap) {
	m_x = x;
	m_y = y;
	hitpoints = hit;
	armorpoints = armor;
	strengthpoints = strength;
	dexteritypoints = dex;
	currweapon = weap;
	sleeptime = 0;
}
Actor::~Actor() {
	if (currweapon != nullptr) {
		delete currweapon;
	}
}
void Actor::changesleep(int time) {
	if (time > sleeptime) {
		sleeptime = time;
	}
}
bool Actor::decrementsleep() {
	if (sleeptime > 0) {
		sleeptime--;
		return true;
	}
	else {
		return false;
	}
}
std::string Actor::hit(Actor* target) {
	int attackerPoints = dexteritypoints + currweapon->getdex();
	int defenderPoints = target->getdex() + (target->getweapon())->getdex();
	std::string message = getname() + " " + getweapon()->attackstring() + " " + target->getname();
	if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
		//attack hit successfully
		target->changehit(-randInt(0, strengthpoints + currweapon->getdamage() - 1));
		int sleeptime = currweapon->sleeptime();
		if (target->gethit() <= 0) {
			return message + " dealing a final blow.";
		}
		else if (sleeptime != 0) {
			target->changesleep(sleeptime);
			return message + " and hits, putting " + target->getname() + " to sleep.";
		}
		else {
			return message + " and hits.";
		}
	}
	return message + " and misses.";
}



