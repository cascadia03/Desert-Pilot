#include "DXUT.h"
#include "boss_2.h"

#include "game_system.h"
#include "player.h"
#include "bullet.h"
#include "effect.h"
#include "item.h"

void boss_2::Init()
{
	SOUND_M->Play("boss_appear", false)->SetVolume(-1000);
	pos = { WINSIZEX / 2, -128 };
	hp = 7500;
	phase = 0;
}

void boss_2::Update()
{
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));

	switch (phase)
	{
	case 0:
		pos.y += 4;
		if (pos.y > 180)
		{
			phase++;
			timer[0] = 0;
			timer[1] = 0;
			p_angle[1] = 0;
			p_angle[2] = 0;
			speed = 1;
		}
		break;
	case 1:
		//pattern 1
		if (timer[1] >= 20)
		{
			if (timer[1] % 5 == 0)
			{
				for (float i = 0.f; i < 360.f; i += 40.f)
					OBJECT_M->Add(new bullet("enemy", pos.x, pos.y + 24, 8.f, p_angle[1] + i, 0.65f, 15, TYPE::SPECIAL));
			}
			if (timer[1] >= 30)
			{
				timer[1] = 0;
				p_angle[1] += 15.f;
			}
		}
		timer[1]++;

		//pattern 2
		if (timer[2] % 15 == 0)
		{
			for (float i = 0.f; i < 360.f; i += 30.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y + 24, 10.f, p_angle[2] + i, 0.5f, 10, TYPE::NORMAL));
			p_angle[2] -= 8.f;
		}
		timer[2]++;

		if (hp <= 5000)
		{
			SOUND_M->Play("effect", false)->SetVolume(-1000);
			OBJECT_M->Add(new effect_2(pos.x, pos.y, 1.f, 90, VECTOR3(255, 0, 0)));
			OBJECT_M->Delete("bullet", "enemy");
			phase++;
			timer[0] = 0;
			angle = rand() % 360;
			p_angle[0] = 0.f;
			p_angle[1] = 0.f;
			direction = { cos(D3DXToRadian(angle)), sin(D3DXToRadian(angle)) };
		}
		break;
		
	case 2:
		//pattern 1
		if (timer[1] >= 120)
		{
			if (timer[1] == 120)
			{
				angle = rand() % 360;
				direction = { cos(D3DXToRadian(angle)), sin(D3DXToRadian(angle)) };
			}

			speed = 5;
			if (timer[1] % 15 == 0)
			{
				VECTOR2 _direction;
				if (_player) D3DXVec2Normalize(&_direction, &(_player->pos - pos));
				p_angle[1] = D3DXToDegree(atan2f(_direction.y, _direction.x));
				for (int i = - 30; i <= 30; i += 15)
					OBJECT_M->Add(new bullet("enemy", pos.x, pos.y + 24, 10.f, p_angle[1] + i, 0.65f, 15, TYPE::SPECIAL));
			}
			if (timer[1] >= 150)
			{
				speed = 1;
				timer[1] = 0;
			}
		}
		timer[1]++;

		//pattern 2
		if (timer[2] % 20 == 0)
		{
			for (float i = 0.f; i < 360.f; i += 40.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y + 24, 6.f, p_angle[2] + i, 0.5f, 10, TYPE::NORMAL));
			p_angle[2] += 12.f;
		}
		timer[2]++;

		pos += direction * speed;

		//collide
		if (collider.left < 0) direction.x = abs(direction.x);
		if (collider.right > WINSIZEX) direction.x = -abs(direction.x);
		if (collider.top < 0) direction.y = abs(direction.y);
		if (collider.bottom > 360) direction.y = -abs(direction.y);

		if (hp <= 2500)
		{
			SOUND_M->Play("effect", false)->SetVolume(-1000);
			OBJECT_M->Add(new effect_2(pos.x, pos.y, 1.f, 90, VECTOR3(255, 0, 0)));
			OBJECT_M->Delete("bullet", "enemy");
			phase++;
			timer[0] = 0;
		}
		break;
	case 3:
		for (int i = 0; i < 10; i++)
		{
			D3DXVec2Normalize(&direction, &(VECTOR2(WINSIZEX / 2, 180) - pos));
			pos += direction;
		}

		if (timer[0] >= 60)
		{
			phase++;
			direction = { 1, 0 };
			timer[1] = 0;
			timer[2] = 10;
			timer[3] = 0;
			p_angle[1] = 0;
			p_angle[2] = 0;
			p_angle[3] = 0;
		}
		break;
	case 4:
		if (timer[1] % 20 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 45.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 5.f, p_angle[1] + i, 0.65f, 10, TYPE::NORMAL));
			p_angle[1] += 3.f;
		}
		timer[1]++;

		if (timer[2] % 20 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 45.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 6.f, p_angle[2] + i, 0.5f, 10, TYPE::NORMAL));
			p_angle[2] -= 12.f;
		}
		timer[2]++;

		if (timer[3] % 45 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 24.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 4.f, p_angle[3] + i, 0.7f, 10, TYPE::SPECIAL));
			p_angle[3] += 8.f;
		}
		timer[3]++;

		if (collider.left < 32) direction.x = abs(direction.x);
		if (collider.right > WINSIZEX - 32) direction.x = -abs(direction.x);
		pos += direction * 2;

		if (hp <= 0)
		{
			SOUND_M->Play("effect", false)->SetVolume(-1000);
			OBJECT_M->Delete("bullet", "enemy");
			phase++;
			timer[0] = 0;
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
		SOUND_M->Play("bomb_1", false)->SetVolume(-1500);
		static_cast<game_system*>(OBJECT_M->Find("game_system"))->score += 20000;
		if (_player)
			static_cast<player*>(OBJECT_M->Find("player"))->exp += 150;
		Destroy();
	}
}

void boss_2::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("boss_2"), pos.x, pos.y, 0.6f, 1.f, 1.f, 90.f);
	//hp
	RENDER_M->Render(IMAGE_M->Find("hp"), 748, 20, 0.1f, hp / 7500.f, 1.f, 0.f, D3DCOLOR_RGBA(255, 0, 0, 255));
	RENDER_M->Render(IMAGE_M->Find("hp"), 748, 20, 0.15f, 1.f, 1.f, 0.f, D3DCOLOR_RGBA(64, 64, 64, 123));
}

void boss_2::Release()
{
	OBJECT_M->Add(new effect_2(pos.x, pos.y, 2.f, 120, VECTOR3(255, 0, 0)));
}
