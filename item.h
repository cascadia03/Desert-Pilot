#pragma once
#include "object_manager.h"

class cooltimeReset : public object
{
public:
	VECTOR2 pos;
	RECT collider;
public:
	cooltimeReset(float _x, float _y) : object("item", "cooltimeReset") 
	{
		pos = { _x, _y };
	}
	virtual ~cooltimeReset() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

class Healkit : public object
{
public:
	VECTOR2 pos;
	RECT collider;
public:
	Healkit(float _x, float _y) : object("item", "Healkit") 
	{
		pos = { _x, _y };
	}
	virtual ~Healkit() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

class levelupgrade : public object
{
public:
	VECTOR2 pos;
	RECT collider;
public:
	levelupgrade(float _x, float _y) : object("item", "levelupgrade")
	{
		pos = { _x, _y };
	}
	virtual ~levelupgrade() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};