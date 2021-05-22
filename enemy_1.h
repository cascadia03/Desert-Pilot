#pragma once
#include "enemy.h"

class enemy_1 : public enemy
{
public:
	enemy_1(float _x, float _y, float _angle) : enemy("one") 
	{
		pos = { _x, _y };
		angle = _angle;
	}
	virtual ~enemy_1() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};