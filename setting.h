#pragma once
#include "scene_manager.h"

class setting : public scene
{
public:
	setting() {}
	virtual ~setting() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};