#pragma once
#include "scene_manager.h"

class stage_1 : public scene
{
public:
	int phase;
	int timer;
public:
	stage_1() {}
	virtual ~stage_1() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

