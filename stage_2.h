#pragma once
#include "scene_manager.h"

class stage_2 : public scene
{
public:
	int phase;
	int timer;
public:
	stage_2() {}
	virtual ~stage_2() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};