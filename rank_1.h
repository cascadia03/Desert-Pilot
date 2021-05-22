#pragma once
#include "scene_manager.h"

class rank_1 : public scene
{
public:
	int timer;
public:
	rank_1() {}
	virtual ~rank_1() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

