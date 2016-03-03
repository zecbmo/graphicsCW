// Input class

#include "Input.h"

void Input::SetKeyDown(WPARAM key)
{
	keys[key] = true;
}

void Input::SetKeyUp(WPARAM key)
{
	keys[key] = false;
}

bool Input::IsKeyDown(int key)
{
	return keys[key];
}

void Input::SetMouseX(int pos)
{
	mouse.x = pos;
}

void Input::SetMouseY(int pos)
{
	mouse.y = pos;
}

int Input::GetMouseX()
{
	return mouse.x;
}

int Input:: GetMouseY()
{
	return mouse.y;
}

