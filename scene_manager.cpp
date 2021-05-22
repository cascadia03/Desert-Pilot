#include "DXUT.h"
#include "scene_manager.h"

scene_manager::scene_manager() : now(nullptr), next(nullptr)
{
}

scene_manager::~scene_manager()
{
	for (auto i : scenes)
		SAFE_DELETE(i.second);
	scenes.clear();
}

void scene_manager::Update()
{
	if (next)
	{
		if (now) now->Release();
		next->Init();
		now = next;
		next = nullptr;
	}
	if (now) now->Update();
}

void scene_manager::Render()
{
	if (now) now->Render();
}

void scene_manager::Add(string _key, scene * _scene)
{
	scenes[_key] = _scene;
}

void scene_manager::Change(string _key)
{
	next = scenes[_key];
}
