#include "DXUT.h"
#include "object_manager.h"

object_manager::object_manager()
{
}

object_manager::~object_manager()
{
	for (auto i : objects)
	{
		i->Release();
		SAFE_DELETE(i);
	}
}

void object_manager::Update()
{
	for (auto i = objects.begin(); i != objects.end();)
	{
		if ((*i)->IsDestroy)
		{
			(*i)->Release();
			SAFE_DELETE(*i);
			i = objects.erase(i);
		}
		else
		{
			(*i)->Update();
			i++;
		}
	}
}

void object_manager::Render()
{
	for (auto i : objects)
		i->Render();
}

void object_manager::Add(object * _object)
{
	_object->Init();
	objects.push_back(_object);
}

void object_manager::Delete(object * _object)
{
	for (auto i = objects.begin(); i != objects.end();)
	{
		if ((*i) == _object)
		{
			(*i)->Release();
			SAFE_DELETE(*i);
			i = objects.erase(i);
		}
		else i++;
	}
}

void object_manager::Delete(string _type)
{
	for (auto i = objects.begin(); i != objects.end();)
	{
		if ((*i)->type == _type)
		{
			(*i)->Release();
			SAFE_DELETE(*i);
			i = objects.erase(i);
		}
		else i++;
	}
}

void object_manager::Delete(string _type, string _tag)
{
	for (auto i = objects.begin(); i != objects.end();)
	{
		if ((*i)->type == _type && (*i)->tag == _tag)
		{
			(*i)->Release();
			SAFE_DELETE(*i);
			i = objects.erase(i);
		}
		else i++;
	}
}

object * object_manager::Find(string _type)
{
	for (auto i : objects)
	{
		if (i->type == _type)
			return i;
	}
	return nullptr;
}

object * object_manager::Find(string _type, string _tag)
{
	for (auto i : objects)
	{
		if (i->type == _type && i->tag == _tag)
			return i;
	}
	return nullptr;
}

list<object*> object_manager::FindList(string _type)
{
	list<object*> list;

	for (auto i : objects)
	{
		if (i->type == _type)
			list.push_back(i);
	}

	return list;
}

list<object*> object_manager::FindList(string _type, string _tag)
{
	list<object*> list;

	for (auto i : objects)
	{
		if (i->type == _type && i->tag == _tag)
			list.push_back(i);
	}

	return list;
}
