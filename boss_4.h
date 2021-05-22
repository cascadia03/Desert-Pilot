#pragma once
#include "enemy.h"

class boss_4 : public enemy
{
public:
	int phase;
public:
	boss_4() : enemy("boss") {}
	virtual ~boss_4() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};