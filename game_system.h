#pragma once
#include "object_manager.h"

class game_system : public object
{
public:
	//score
	string ranked_name[5];
	int ranked_score[5];
	int score;

	//error
	int skill_error;

	//cheat
	bool showStat;

	//background
	int background_red;
	int background_black;
	float background_y;
	float scroll_speed;
public:
	game_system() : object("game_system") {}
	virtual ~game_system() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void rankUpdate(string _name);
};