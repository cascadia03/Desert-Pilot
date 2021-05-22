#include "DXUT.h"
#include "boss_3.h"

#include "game_system.h"
#include "player.h"
#include "bullet.h"
#include "effect.h"
#include "item.h"

void boss_3::Init()
{
	SOUND_M->Play("boss_appear", false)->SetVolume(-1000);
	pos = { WINSIZEX / 2, -128 };
	hp = 12000;
	phase = 0;
}

void boss_3::Update()
{
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));

	switch (phase)
	{
	case 0:
		pos.y += 4;
		if (pos.y > 180)
		{
			phase++;
			direction = { 1, 0 };
			timer[1] = 0;
			timer[2] = 0;
			timer[3] = 0;
			p_angle[1] = 0;
			p_angle[2] = 0;
			p_angle[3] = 0;
		}
		break;
	case 1:
		//pattern 1
		if (timer[1] % 30 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 45.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 5.f, p_angle[1] + i, 0.65f, 10, TYPE::SPECIAL));
			p_angle[1] += 3.f;
		}
		timer[1]++;

		//pattern 2
		if (timer[2] % 15 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 36.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 6.f, p_angle[2] + i, 0.5f, 10, TYPE::NORMAL));
			p_angle[2] += 6.f;
		}
		timer[2]++;

		//pattern 3
		if (timer[3] % 45 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 24.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 8.f, p_angle[3] + i, 0.4f, 10, TYPE::NORMAL));
			p_angle[3] += 15.f;
		}
		timer[3]++;

		if (collider.left < 32) direction.x = abs(direction.x);
		if (collider.right > WINSIZEX - 32) direction.x = -abs(direction.x);
		pos += direction * 2;

		if (hp <= 8000)
		{
			SOUND_M->Play("effect", false)->SetVolume(-1000);
			OBJECT_M->Add(new effect_2(pos.x, pos.y, 1.f, 90, VECTOR3(255, 0, 0)));
			OBJECT_M->Delete("bullet", "enemy");
			phase++;
			timer[0] = 0;
			timer[1] = 120;
			direction = { 0, 0 };
		}
		break;
	case 2:
		//pattern 1
		if (timer[1] >= 240)
		{
			if (timer[1] == 240)
			{
				if (_player) D3DXVec2Normalize(&direction, &(_player->pos - pos));
				p_angle[1] = D3DXToDegree(atan2f(direction.y, direction.x));
			}

			if (timer[1] % 2 == 0)
			{
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, rand() % 3 + 6.f, p_angle[1] + rand() % 120 + 30, rand() % 4 * 0.1f + 0.6f, 10, TYPE::SPECIAL));
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, rand() % 3 + 6.f, p_angle[1] + rand() % 120 + 210, rand() % 4 * 0.1f + 0.6f, 10, TYPE::SPECIAL));
			}

			pos += direction * 15;

			if (pos.y > WINSIZEY + 128)
			{
				pos = { WINSIZEX / 2, -128 };
				timer[1] = 0;
			}
		}
		else if (pos.y < 180) pos.y += 6;
		else if (hp <= 4000)
		{
			SOUND_M->Play("effect", false)->SetVolume(-1000);
			OBJECT_M->Add(new effect_2(pos.x, pos.y, 1.f, 90, VECTOR3(255, 0, 0)));
			OBJECT_M->Delete("bullet", "enemy");
			phase++;
			timer[0] = 0;
			timer[1] = 0;
			timer[2] = 0;
			angle = rand() % 360;
			direction = { cos(D3DXToRadian(angle)), sin(D3DXToRadian(angle)) };
			speed = 1;
			break;
		}
		timer[1]++;

		//pattern 2
		if (timer[2] % 60 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 36.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 5.f, p_angle[2] + i, 0.6f, 10, TYPE::NORMAL));
			p_angle[2] += 6.f;
		}
		timer[2]++;

		break;
	case 3:
		//pattern 1
		if (timer[1] >= 120)
		{
			if (timer[1] == 120)
			{
				angle = rand() % 360;
				direction = { cos(D3DXToRadian(angle)), sin(D3DXToRadian(angle)) };
			}

			speed = 5;

			if (timer[1] >= 150)
			{
				speed = 1;
				timer[1] = 0;
			}
		}
		timer[1]++;

		//pattern 2
		if (timer[2] >= 90)
		{
			if (timer[2] % 24 == 0)
			{
				VECTOR2 _direction;
				if (_player)
					D3DXVec2Normalize(&_direction, &(_player->pos - pos));
				p_angle[2] = D3DXToDegree(atan2f(_direction.y, _direction.x));
				for (int i = 0; i < 12; i++)
					OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 4.f + rand() % 5, p_angle[2] + rand() % 120 - 60.f, rand() % 5 * 0.1 + 0.5f, 12, TYPE::NORMAL));
			}
			if (timer[2] >= 162) timer[2] = 0;
		}
		timer[2]++;

		//pattern 3
		if (timer[3] % 5 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 90.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 7.f, p_angle[3] + i, 0.5f, 10, TYPE::SPECIAL));
			p_angle[3] += 12.f;
		}
		timer[3]++;

		pos += direction * speed;

		//collide
		if (collider.left < 0) direction.x = abs(direction.x);
		if (collider.right > WINSIZEX) direction.x = -abs(direction.x);
		if (collider.top < 0) direction.y = abs(direction.y);
		if (collider.bottom > 360) direction.y = -abs(direction.y);

		if (hp <= 0)
		{
			SOUND_M->Play("effect", false)->SetVolume(-1000);
			SOUND_M->Play("bomb_1", false)->SetVolume(-1500);
			OBJECT_M->Delete("bullet", "enemy");
			phase++;
			timer[0] = 0;
			timer[1] = 0;
		}
		break;
	}
	timer[0]++;

	//collider
	if (phase == 0) SetRect(&collider, -256, -256, -256, -256);
	else SetRect(&collider, pos.x - 56, pos.y - 56, pos.x + 56, pos.y + 56);

	//Destroy
	if (hp <= 0)
	{
		static_cast<game_system*>(OBJECT_M->Find("game_system"))->score += 30000;
		if (_player)
			static_cast<player*>(OBJECT_M->Find("player"))->exp += 200;
		Destroy();
	}
}

void boss_3::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("boss_3"), pos.x, pos.y, 0.6f, 1.f, 1.f, 90.f);
	//hp
	RENDER_M->Render(IMAGE_M->Find("hp"), 748, 20, 0.1f, hp / 12000.f, 1.f, 0.f, D3DCOLOR_RGBA(255, 0, 0, 255));
	RENDER_M->Render(IMAGE_M->Find("hp"), 748, 20, 0.15f, 1.f, 1.f, 0.f, D3DCOLOR_RGBA(64, 64, 64, 123));
}

void boss_3::Release()
{
	OBJECT_M->Add(new effect_2(pos.x, pos.y, 2.f, 120, VECTOR3(255, 0, 0)));
}