#pragma once
#include "scene_manager.h"

class rank_2 : public scene
{
public:
	string initial;
	int timer;
public:
	rank_2() {}
	virtual ~rank_2() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};
