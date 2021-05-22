#include "DXUT.h"
#include "enemy_2.h"

#include "game_system.h"
#include "player.h"
#include "bullet.h"
#include "effect.h"
#include "item.h"

void enemy_2::Init()
{
	direction = { cos(D3DXToRadian(angle)), sin(D3DXToRadian(angle)) };
	hp = 150;
}

void enemy_2::Update()
{
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));

	//pattern 1
	if (timer[0] == 0) speed = 3;
	if (timer[0] % 90 == 0 && timer[0] < 480)
	{
		speed = 2;
		angle += rand() % 180 - 90;
		direction = { cos(D3DXToRadian(angle)), sin(D3DXToRadian(angle)) };
	}
	if (timer[0] == 480)
	{
		speed = 3;
		angle = rand() % 180 + 180;
		direction = { cos(D3DXToRadian(angle)), sin(D3DXToRadian(angle)) };
	}
	timer[0]++;

	//pattern 2
	if (timer[1] >= 90)
	{
		if (timer[1] == 90)
		{
			VECTOR2 _direction;
			if (_player)
				D3DXVec2Normalize(&_direction, &(_player->pos - pos));
			p_angle[1] = D3DXToDegree(atan2f(_direction.y, _direction.x));
		}
		if (timer[1] % 15== 0)
			OBJECT_M->Add(new bullet("enemy", pos.x, pos.y + 24, 8.f, p_angle[1], 0.5f, 10, TYPE::NORMAL));
		if (timer[1] >= 120) timer[1] = 0;
	}
	timer[1]++;

	//collide
	if (timer[0] < 480)
	{
		if (collider.left < 0) direction.x = abs(direction.x);
		if (collider.right > WINSIZEX) direction.x = -abs(direction.x);
		if (collider.top < 0) direction.y = abs(direction.y);
		if (collider.bottom > 360) direction.y = -abs(direction.y);
	}
	if (timer[0] >= 480)
		if (collider.top < -64 || collider.right < -64 || collider.left > WINSIZEX + 64) Destroy();

	RECT temp;
	if (_player)
	{
		if (IntersectRect(&temp, &collider, &_player->collider))
		{
			_player->hp -= 40;
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
		static_cast<game_system*>(OBJECT_M->Find("game_system"))->score += 2500;
		if (_player)
			static_cast<player*>(OBJECT_M->Find("player"))->exp += 30;
		Destroy();
	}
}

void enemy_2::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("enemy_2"), pos.x, pos.y, 0.6f, 1.f, 1.f, 90.f);
}

void enemy_2::Release()
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