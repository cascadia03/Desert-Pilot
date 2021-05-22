#include "DXUT.h"
#include "item.h"

#include "player.h"

//cooltimeReset
void cooltimeReset::Init()
{
}

void cooltimeReset::Update()
{
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));

	pos.y += 1;
	SetRect(&collider, pos.x - 20, pos.y - 20, pos.x + 20, pos.y + 20);
	if (collider.bottom > WINSIZEY + 64) Destroy();
	if (_player)
	{
		RECT temp;
		if (IntersectRect(&temp, &collider, &_player->collider))
		{
			_player->bomb_cooltimer = 1800;
			_player->shield_cooltimer = 600;
			Destroy();
		}
	}
}

void cooltimeReset::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("cooltimeReset"), pos.x, pos.y, 0.3f);
}

void cooltimeReset::Release()
{
}

//Healkit
void Healkit::Init()
{
}

void Healkit::Update()
{
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));

	pos.y += 1;
	SetRect(&collider, pos.x - 20, pos.y - 20, pos.x + 20, pos.y + 20);
	if (collider.bottom > WINSIZEY + 64) Destroy();
	if (_player)
	{
		RECT temp;
		if (IntersectRect(&temp, &collider, &_player->collider))
		{
			_player->hp += _player->max_hp * 0.2;
			Destroy();
		}
	}
}

void Healkit::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("healkit"), pos.x, pos.y, 0.3f);
}

void Healkit::Release()
{
}

//levelupgrade
void levelupgrade::Init()
{
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));

	if (_player)
		if (_player->level >= 5)
			Destroy();
}

void levelupgrade::Update()
{
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));

	pos.y += 1;
	SetRect(&collider, pos.x - 20, pos.y - 20, pos.x + 20, pos.y + 20);
	if (collider.bottom > WINSIZEY + 64) Destroy();
	if (_player)
	{
		RECT temp;
		if (IntersectRect(&temp, &collider, &_player->collider))
		{
			_player->exp = _player->max_exp;
			Destroy();
		}
	}
}

void levelupgrade::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("levelup"), pos.x, pos.y, 0.3f);
}

void levelupgrade::Release()
{
}