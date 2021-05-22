#pragma once
#include "singleton.h"

class object abstract
{
public:
	string type;
	string tag;
	bool IsDestroy;
public:
	object(string _type) : type(_type), tag("none"), IsDestroy(false) {}
	object(string _type, string _tag) : type(_type), tag(_tag), IsDestroy(false) {}
	virtual ~object() {}

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

	void Destroy() { IsDestroy = true; }
};

class object_manager : public singleton<object_manager>
{
private:
	list<object*> objects;
public:
	object_manager();
	~object_manager();

	void Update();
	void Render();

	void Add(object* _object);
	void Delete(object* _object);
	void Delete(string _type);
	void Delete(string _type, string _tag);
	object* Find(string _type);
	object* Find(string _type, string _tag);
	list<object*> FindList(string _type);
	list<object*> FindList(string _type, string _tag);
};

#define OBJECT_M object_manager::GetInst()