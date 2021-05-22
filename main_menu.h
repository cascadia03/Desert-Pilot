#pragma once
#include "scene_manager.h"

class main_menu : public scene
{
public:
	int phase;

	//title
	VECTOR2 t_pos;
	int t_alpha;

	//menu
	int selection;
	int m_alpha[4];
	float m_size[4];
public:
	main_menu() {}
	virtual ~main_menu() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};