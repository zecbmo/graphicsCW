#pragma once

#include "GameObject.h"
#include "Cone.h"

class TronRecogniser : public GameObject
{
public:
	TronRecogniser() {};
	~TronRecogniser() {};

	void Init(float depth);
	void Update();
	void Render();



private:
	Shapes left_leg_;
	Shapes left_foot_;
	Shapes right_leg_;
	Shapes right_foot_;

	Shapes leg_brigde_;
	Shapes ballsack_;

	Shapes left_sqaure_;
	Shapes right_sqaure_;

	Shapes left_mini_;
	Shapes right_mini_;

	Shapes centre_square_;

	Shapes left_top_;
	Shapes right_top_;

	Shapes centre_quad_;
	Shapes top_hat_;




};