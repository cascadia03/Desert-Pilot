#include "DXUT.h"
#include "input_manager.h"

input_manager::input_manager()
{
	ZeroMemory(Current, 256);
	ZeroMemory(Prevent, 256);
}

input_manager::~input_manager()
{
}

void input_manager::Update()
{
	memcpy(Prevent, Current, 256);
	for (int i = 0; i < 256; i++)
		Current[i] = GetAsyncKeyState(i) & 0x8000;
}

bool input_manager::Pressed(int _key)
{
	return Current[_key] && !Prevent[_key];
}

bool input_manager::Pressing(int _key)
{
	return Current[_key] && Prevent[_key];
}

bool input_manager::Released(int _key)
{
	return !Current[_key] && Prevent[_key];
}
