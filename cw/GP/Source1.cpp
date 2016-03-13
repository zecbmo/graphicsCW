#include "GameObject.h"

class Ship : public GameObject
{
public:
	Ship();
	~Ship();

private:

};

Ship::Ship()
{
}

Ship::~Ship()
{
}

Ship* prefab = new Ship;
vector<*Ship> ships;