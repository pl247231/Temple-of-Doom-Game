#ifndef  PLAYER
#define PLAYER

#include<vector>
#include "Actor.h"
#include "Object.h"
class Object;

class Player : public Actor
{
public:
	Player(int x, int y);
	~Player();
	virtual std::string getname() {
		return "Player";
	}
	void addtoinventory(Object* obj) {
		inventory.push_back(obj);
	}
	virtual void heal();
	std::string equip(int index);
	std::string read(int index);
	std::vector<Object*>& getinventory() {
		return inventory;
	}
private:
	std::vector<Object*> inventory;
	int maxhealth;
};

#endif // ! PLAYER