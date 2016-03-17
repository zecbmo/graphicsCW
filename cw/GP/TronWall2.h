#pragma once
#include "GameObject.h"

class TronWall2 : public GameObject
{
public:
	TronWall2() {};
	~TronWall2() {};

	void Init(float depth);
	void Update();
	void Render();


private:
	Shapes block_one_;
	Shapes block_two_;
	Shapes block_three_;
	Shapes block_four_;


};