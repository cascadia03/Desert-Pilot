#pragma once
#include "enemy.h"

class enemy_3 : public enemy
{
public:
	enemy_3(float _x, float _y) : enemy("three")
	{
		pos = { _x, _y };
	}
	virtual ~enemy_3() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};