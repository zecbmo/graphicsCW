#pragma once

#include "GameObject.h"

class Widget : public GameObject
{
public:
	Widget() {};
	~Widget() {};

	void Update(Vector3 position);
	void Render();

private:

};
