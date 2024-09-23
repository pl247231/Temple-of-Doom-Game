#include "Monster.h"

Object* Bogeyman::drop() {
	//random drop
	if (trueWithProbability(0.1)) {
		return new Axe(this->getx(), this->gety());
	}
	return nullptr;
}
Object* Snakewoman::drop() {
	//random drop
	if (trueWithProbability(1.0 / 3)) {
		return new Fangs(this->getx(), this->gety());
	}
	return nullptr;
}
Object* Dragon::drop() {
	//random drop
	int type = randInt(1, 5);
	switch (type) {
	case 1:
		return new Scrollteleport(getx(), gety());
	case 2:
		return new Scrollstrength(getx(), gety());
	case 3:
		return new Scrollarmor(getx(), gety());
	case 4:
		return new Scrollhealth(getx(), gety());
	default:
		return new Scrolldex(getx(), gety());
	}
}
void Dragon::heal() {
	//0.1 chance to heal
	if (gethit() < maxhealh && trueWithProbability(0.1)) {
		incrementhit();
	}
}
Object* Goblin::drop() {
	//random drop
	if (trueWithProbability(1.0 / 3)) {
		if (trueWithProbability(0.5)) {
			return new Axe(getx(), gety());
		}
		else {
			return new Fangs(getx(), gety());
		}
	}
	return nullptr;
}