#pragma once
#include "object_manager.h"

class enemy : public object
{
public:
	VECTOR2 pos;
	VECTOR2 direction;
	RECT collider;
	float angle;
	float speed;
	int hp;

	//timer & angle
	int timer[8];
	int p_angle[8];
public:
	enemy(string _tag) : object("enemy", _tag)
	{
		for (auto& i : timer)
			i = 0;
	}
	virtual ~enemy() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

