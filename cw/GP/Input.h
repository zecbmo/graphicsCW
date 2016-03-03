#ifndef INPUT_H
#define INPUT_H
// Input class


#include <Windows.h>

class Input
{
	typedef struct Mouse
	{
		int x,y;
		bool left, right;
	};

public:
	void SetKeyDown(WPARAM);
	void SetKeyUp(WPARAM);

	bool IsKeyDown(int);
	void SetMouseX(int);
	void SetMouseY(int);
	int GetMouseX();
	int GetMouseY();
	// set mouse botton down (left, right, middle)
	// set mouse botton up

private:
	bool keys[256];
	Mouse mouse;

};

#endif