#ifndef OBJECT
#define OBJECT

#include<string>
#include "utilities.h"

//functions implemented in h file since they are 1-2 lines
class Object
{
public:
	Object(int x, int y) {
		m_x = x;
		m_y = y;
	}
	virtual ~Object() {}
	virtual std::string getname() = 0;
	int getx() {
		return m_x;
	}
	int gety() {
		return m_y;
	}
	void setx(int x) {
		m_x = x;
	}
	void sety(int y) {
		m_y = y;
	}
private:
	int m_x, m_y;
};

class Weapon : public Object
{
public:
	Weapon(int x, int y, int dex, int damage) : Object(x, y) {
		dexbonus = dex;
		damageamt = damage;
	}
	virtual ~Weapon() {}
	int getdex() {
		return dexbonus;
	}
	int getdamage() {
		return damageamt;
	}
	virtual std::string getaction() = 0;
	virtual int sleeptime() {
		return 0;
	}
	std::string attackstring() {
		return getaction() + " " + getname() + " at";
	}
private:
	int dexbonus, damageamt;
};

class Mace : public Weapon
{
public:
	Mace(int x = 0, int y = 0) : Weapon(x, y, 0, 2) {}
	virtual ~Mace() {}
	virtual std::string getname() {
		return "mace";
	}
	virtual std::string getaction() {
		return "swings";
	}
};

class Shortsword : public Weapon
{
public:
	Shortsword(int x = 0, int y = 0) : Weapon(x, y, 0, 2) {}
	virtual ~Shortsword() {}
	virtual std::string getname() {
		return "short sword";
	}
	virtual std::string getaction() {
		return "slashes";
	}
};

class Longsword : public Weapon
{
public:
	Longsword(int x = 0, int y = 0) : Weapon(x, y, 2, 4) {}
	virtual ~Longsword() {}
	virtual std::string getname() {
		return "long sword";
	}
	virtual std::string getaction() {
		return "swings";
	}
};


class Axe : public Weapon {
public:
	Axe(int x = 0, int y = 0) : Weapon(x, y, 5, 5) {}
	virtual ~Axe() {}
	virtual std::string getname() {
		return "magic axe";
	}
	virtual std::string getaction() {
		return "chops";
	}
};

class Fangs : public Weapon {
public:
	Fangs(int x = 0, int y = 0) : Weapon(x, y, 3, 2) {}
	virtual ~Fangs() {}
	virtual std::string getname() {
		return "magic fangs of sleep";
	}
	virtual std::string getaction() {
		return "strikes";
	}
	virtual int sleeptime() {
		if (trueWithProbability(0.2)) {
			return randInt(2, 6);
		}
		return 0;
	}
};

class Scroll : public Object
{
public:
	Scroll(int x, int y) : Object(x, y) {}
	virtual std::string getname() {
		return "scroll of ";
	}
	virtual char gettype() = 0;
	virtual std::string readtext() = 0;
};

class Scrollteleport : public Scroll {
public:
	Scrollteleport(int x = 0, int y = 0) : Scroll(x, y) { }
	virtual std::string getname() {
		return Scroll::getname() + "teleportation";
	}
	virtual char gettype() {
		return 't';
	}
	virtual std::string readtext() {
		return "You feel your body wrenched in space and time.";
	}
};

class Scrollstrength : public Scroll {
public:
	Scrollstrength(int x = 0, int y = 0) : Scroll(x, y) { }
	virtual std::string getname() {
		return Scroll::getname() + "strength";
	}
	virtual char gettype() {
		return 's';
	}
	virtual std::string readtext() {
		return "Your muscles bulge.";
	}
};

class Scrollarmor : public Scroll {
public:
	Scrollarmor(int x = 0, int y = 0) : Scroll(x, y) { }
	virtual std::string getname() {
		return Scroll::getname() + "enhance armor";
	}
	virtual char gettype() {
		return 'a';
	}
	virtual std::string readtext() {
		return "Your armor glows blue.";
	}
};

class Scrollhealth : public Scroll {
public:
	Scrollhealth(int x = 0, int y = 0) : Scroll(x, y) { }
	virtual std::string getname() {
		return Scroll::getname() + "enhance health";
	}
	virtual char gettype() {
		return 'h';
	}
	virtual std::string readtext() {
		return "You feel your heart beating stronger.";
	}
};

class Scrolldex : public Scroll {
public:
	Scrolldex(int x = 0, int y = 0) : Scroll(x, y) { }
	virtual std::string getname() {
		return Scroll::getname() + "enhance dexterity";
	}
	virtual char gettype() {
		return 'd';
	}
	virtual std::string readtext() {
		return "You feel like less of a klutz.";
	}
};

class Stair : public Object {
public:
	Stair(int x = 0, int y = 0) : Object(x, y) {}
	virtual std::string getname() {
		return "Stair";
	}
};

class Idol : public Object {
public:
	Idol(int x = 0, int y = 0) : Object(x, y) {}
	virtual std::string getname() {
		return "the golden idol";
	}
};
#endif // !OBJECT