#pragma once
#include "enemy.h"

class enemy_2 : public enemy
{
public:
	enemy_2(float _x, float _y, float _angle) : enemy("two")
	{
		pos = { _x, _y };
		angle = _angle;
	}
	virtual ~enemy_2() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};