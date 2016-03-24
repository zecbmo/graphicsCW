#pragma once

#include "GameObject.h"

class Cone : public GameObject
{
public:
	Cone() {};
	~Cone() {};

	void Init(float height, float resolution, std::string filename );
	void Update(float speed, float dt);
	void Render();
	inline void SetMoving(bool moving) { moving_ = moving; };

private:
	float speed_;
	bool moving_;
};

