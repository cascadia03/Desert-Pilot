#pragma once
#include "object_manager.h"

class shield : public object
{
public:
	VECTOR2* pos;
	RECT collider;
	int timer;
public:
	shield(VECTOR2* _pos) : object("skill", "shield") 
	{
		pos = _pos;
	}
	virtual ~shield() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

class bomb : public object
{
public:
	VECTOR2 pos;
	int timer;
public:
	bomb(VECTOR2 _pos) : object("skill", "bomb")
	{
		pos = _pos;
	}
	virtual ~bomb() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

class levelup : public object
{
public:
	VECTOR2 pos;
	int timer;
public:
	levelup(VECTOR2 _pos) : object("skill", "bomb")
	{
		pos = _pos;
	}
	virtual ~levelup() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};