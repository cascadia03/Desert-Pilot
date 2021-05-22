#pragma once
#include "enemy.h"

class boss_2 : public enemy
{
public:
	int phase;
public:
	boss_2() : enemy("boss") {}
	virtual ~boss_2() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};