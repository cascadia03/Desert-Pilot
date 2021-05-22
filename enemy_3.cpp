#include "DXUT.h"
#include "enemy_3.h"

#include "game_system.h"
#include "player.h"
#include "bullet.h"
#include "effect.h"
#include "item.h"

void enemy_3::Init()
{
	angle = 90.f;
	speed = 1;
	direction = { cos(D3DXToRadian(angle)), sin(D3DXToRadian(angle)) };
	hp = 250;
}

void enemy_3::Update()
{
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));

	//pattern 1
	if (timer[0] >= 120)
	{
		if (timer[0] % 30 == 0)
		{
			for (float i = 150.f; i <= 210.f; i += 15.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y + 24, 6.f, i, 0.4f, 8, TYPE::SPECIAL));
			for (float i = 330.f; i <= 390.f; i += 15.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y + 24, 6.f, i, 0.4f, 8, TYPE::SPECIAL));
		}
		if (timer[0] >= 180) timer[0] = 0;
	}
	timer[0]++;

	//collide
	if (collider.bottom > WINSIZEY + 64) Destroy();
	RECT temp;
	if (_player)
	{
		if (IntersectRect(&temp, &collider, &_player->collider))
		{
			_player->hp -= 60;
			Destroy();
		}
	}

	//movement
	pos += direction * speed;

	//collider
	SetRect(&collider, pos.x - 20, pos.y - 20, pos.x + 20, pos.y + 20);

	//Destroy
	if (hp <= 0)
	{
		SOUND_M->Play("bomb_1", false)->SetVolume(-1500);
		static_cast<game_system*>(OBJECT_M->Find("game_system"))->score += 4000;
		if (_player)
			static_cast<player*>(OBJECT_M->Find("player"))->exp += 60;
		Destroy();
	}
}

void enemy_3::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("enemy_3"), pos.x, pos.y, 0.6f, 1.f, 1.f, 90.f);
}

void enemy_3::Release()
{
	OBJECT_M->Add(new effect_2(pos.x, pos.y, 0.25f, 45.f, VECTOR3(255, 0, 0)));
	if (rand() % 100 <= 10)
	{
		switch (rand() % 3)
		{
		case 0:
			OBJECT_M->Add(new levelupgrade(pos.x, pos.y));
			break;
		case 1:
			OBJECT_M->Add(new cooltimeReset(pos.x, pos.y));
			break;
		case 2:
			OBJECT_M->Add(new Healkit(pos.x, pos.y));
			break;
		}
	}
}