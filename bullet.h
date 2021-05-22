#pragma once
#include "object_manager.h"

enum TYPE { NORMAL, SPECIAL };

class bullet : public object
{
public:
	VECTOR2 pos;
	VECTOR2 direction;
	RECT collider;
	float speed;
	float angle;
	float size;
	int damage;
	TYPE b_type;
public:
	bullet(string _tag, float _x, float _y, float _speed, float _angle, float _size, int _damage, TYPE _b_type) : object("bullet", _tag)
	{
		//stat
		pos = { _x, _y };
		speed = _speed;
		angle = _angle;
		size = _size;
		damage = _damage;
		b_type = _b_type;
	}
	virtual ~bullet() {}

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};