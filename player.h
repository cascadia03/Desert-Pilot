#pragma once
#include "object_manager.h"

class player : public object
{
public:
	VECTOR2 pos;
	RECT collider;

	//stat
	int level;
	int exp;
	int max_exp;
	int hp;
	int max_hp;
	int speed;
	int atk;
	float atk_speed;

	//appear
	bool IsAppear;

	//shooting
	bool weapon_type;
	int shot_cooltimer;

	//shield
	int shield_cooltimer;

	//bomb
	int bomb_cooltimer;
	int bomb_timer;

	//cheat
	bool IsOverpowered;
public:
	player() : object("player") {}
	~player() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

