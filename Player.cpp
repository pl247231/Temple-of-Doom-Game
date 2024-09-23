#include "Player.h"

Player::Player(int x, int y) :Actor(x, y, 20, 2, 2, 2, new Shortsword(0, 0)) {
	maxhealth = 20;
	inventory.push_back(getweapon());
}
Player::~Player() {
	for (Object* obj : inventory) {
		delete obj;
	}
	clearweapon();
}
void Player::heal() {
	//heal with probability 0.1
	if (gethit() < maxhealth && trueWithProbability(0.1)) {
		incrementhit();
	}
}
std::string Player::equip(int index) {
	//if not in inventory return nothing
	if (index >= inventory.size()) {
		return "";
	}
	Weapon* weap = dynamic_cast<Weapon*>(inventory[index]);
	//if not weapon do nothing
	//return string of attempting to equip object
	if (weap != nullptr) {
		setweapon(weap);
		return "You are wielding " + getweapon()->getname();
	}
	return "You can't wield " + inventory[index]->getname();
}
std::string Player::read(int index) {
	//if not in inventory return nothing
	if (index >= inventory.size()) {
		return "";
	}
	Scroll* scroll = dynamic_cast<Scroll*>(inventory[index]);
	//if not scroll do nothing
	//return string of attempting to equip object
	if (scroll != nullptr) {
		char type = scroll->gettype();
		switch (type) {
		case 't':
			break;
		case 'a':
			setarmor(getarmor() + randInt(1, 3));
			break;
		case 's':
			setstrength(getstrength() + randInt(1, 3));
			break;
		case 'h':
			maxhealth += randInt(3, 8);
			break;
		case 'd':
			setdex(getdex() + 1);
			break;
		}
		std::string message = "You read the scroll called " + scroll->getname() + " \n" + scroll->readtext();
		delete inventory[index];
		inventory.erase(inventory.begin() + index);
		return message;
	}
	return "You can't read " + inventory[index]->getname();
}