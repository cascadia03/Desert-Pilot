#pragma once
#include "singleton.h"

class scene abstract
{
public:
	scene() {}
	virtual ~scene() {}

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

class scene_manager : public singleton<scene_manager>
{
private:
	scene* now;
	scene* next;
	map<string, scene*> scenes;
public:
	scene_manager();
	~scene_manager();

	void Update();
	void Render();

	void Add(string _key, scene* _scene);
	void Change(string _key);
};

#define SCENE_M scene_manager::GetInst()