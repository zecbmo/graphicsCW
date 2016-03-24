#pragma once

#include "GameObject.h"

class Cylinder : public GameObject
{
public:
	Cylinder() {};
	~Cylinder() {};

	void Init(float resolution, float height, std::string filename);
	void Update(float speed, float dt);
	void Render();
	inline void SetMoving(bool moving) { moving_ = moving; };
private:
	float speed_;
	bool moving_;
};

