#pragma once
#include "object_manager.h"

class effect_1 : public object
{
public:
	VECTOR2 pos;
	VECTOR3 color;
	float size;
	int timer;
	int cooltimer;
public:
	effect_1(float _x, float _y, float _size, int _timer, VECTOR3 _color) : object("effect", "1")
	{
		pos = { _x, _y };
		size = _size;
		timer = _timer;
		color = _color;
	}
	virtual ~effect_1() {}

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

class effect_2 : public object
{
public:
	VECTOR2 pos;
	VECTOR3 color;
	float size;
	int timer;
	int cooltimer;
public:
	effect_2(float _x, float _y, float _size, int _timer, VECTOR3 _color) : object("effect", "2")
	{
		pos = { _x, _y };
		size = _size;
		timer = _timer;
		color = _color;
	}
	virtual ~effect_2() {}

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};