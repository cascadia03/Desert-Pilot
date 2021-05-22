#pragma once
#include "enemy.h"

class enemy_4 : public enemy
{
public:
	enemy_4(float _x, float _y, float _angle) : enemy("four")
	{
		pos = { _x, _y };
		angle = _angle;
	}
	virtual ~enemy_4() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};