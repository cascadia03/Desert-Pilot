#pragma once
#include "singleton.h"

class input_manager : public singleton<input_manager>
{
private:
	bool Current[256];
	bool Prevent[256];
public:
	input_manager();
	~input_manager();

	void Update();

	bool Pressed(int _key);
	bool Pressing(int _key);
	bool Released(int _key);
};

#define INPUT_M input_manager::GetInst()