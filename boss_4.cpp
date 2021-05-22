#include "DXUT.h"
#include "boss_4.h"

#include "game_system.h"
#include "player.h"
#include "bullet.h"
#include "effect.h"
#include "item.h"

void boss_4::Init()
{
	SOUND_M->Play("boss_appear", false)->SetVolume(-1000);
	pos = { WINSIZEX / 2, -128 };
	hp = 25000;
	phase = 0;
}

void boss_4::Update()
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
			for (float i = 0.f; i <= 360.f; i += 15.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 3.f, p_angle[1] + i, 0.6f, 10, TYPE::SPECIAL));
			p_angle[1] += 3.f;
		}
		timer[1]++;

		//pattern 2
		if (timer[2] % 35 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 20.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 4.f, p_angle[2] + i, 0.7f, 10, TYPE::NORMAL));
			p_angle[2] += 6.f;
		}
		timer[2]++;

		//pattern 3
		if (timer[3] % 40 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 30.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 5.f, p_angle[3] + i, 0.8f, 10, TYPE::NORMAL));
			p_angle[3] += 9.f;
		}
		timer[3]++;

		if (collider.left < 32) direction.x = abs(direction.x);
		if (collider.right > WINSIZEX - 32) direction.x = -abs(direction.x);
		pos += direction;

		if (hp <= 20000)
		{
			SOUND_M->Play("effect", false)->SetVolume(-1000);
			OBJECT_M->Add(new effect_2(pos.x, pos.y, 1.f, 90, VECTOR3(255, 0, 0)));
			OBJECT_M->Delete("bullet", "enemy");
			phase++;
			timer[1] = 120;
			timer[2] = 0;
		}
		break;
	case 2:
		//pattern 1
		if (timer[1] >= 180)
		{
			if (timer[1] == 180)
			{
				if (_player) D3DXVec2Normalize(&direction, &(_player->pos - pos));
			}
			pos += direction * 15;

			if (timer[1] >= 270)
			{
				timer[1] = 179;
				timer[2]++;
				if (timer[2] > 2)
				{
					pos = { WINSIZEX / 2.f, - 128.f };
					timer[1] = 0;
					timer[2] = 0;
				}
				else
				{
					pos = { rand() % 1120 + 80.f, -128.f };
				}
			}

			//pattern 1-1
			if (timer[3] % 15 == 0)
			{
				for (float i = 0.f; i <= 360.f; i += 15.f)
					OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 4.f, p_angle[3] + i, 0.7f, 10, TYPE::SPECIAL));
				p_angle[3] += 4.f;
			}
			timer[3]++;

			//pattern 1-2
			if (timer[4] % 20 == 0)
			{
				for (float i = 0.f; i <= 360.f; i += 30.f)
					OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 6.f, p_angle[4] + i, 0.5f, 10, TYPE::NORMAL));
				p_angle[4] += 7.f;
			}
			timer[4]++;
		}
		else if (pos.y < 180) pos.y += 6;
		else if (hp <= 15000)
		{
			SOUND_M->Play("effect", false)->SetVolume(-1000);
			OBJECT_M->Add(new effect_2(pos.x, pos.y, 1.f, 90, VECTOR3(255, 0, 0)));
			OBJECT_M->Delete("bullet", "enemy");
			phase++;
			timer[0] = 0;
			p_angle[1] = 45;
			break;
		}
		timer[1]++;
		break;
	case 3:
		for (int i = 0; i < 10; i++)
		{
			D3DXVec2Normalize(&direction, &(VECTOR2(WINSIZEX / 2, WINSIZEY / 2) - pos));
			pos += direction;
		}

		if (timer[0] >= 60)
		{
			phase++;
		}
		break;
	case 4:
		if (timer[1] % 5 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 90.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 10.f, p_angle[1] + i, 0.5f, 10, TYPE::NORMAL));
			p_angle[1] += 5.f;
		}
		timer[1]++;

		if (timer[2] % 60 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 60.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 3.f, p_angle[2] + i, 2.f, 30, TYPE::SPECIAL));
			p_angle[2] -= 18.f;
		}
		timer[2]++;


		if (hp <= 10000)
		{
			SOUND_M->Play("effect", false)->SetVolume(-1000);
			OBJECT_M->Add(new effect_2(pos.x, pos.y, 1.f, 90, VECTOR3(255, 0, 0)));
			OBJECT_M->Delete("bullet", "enemy");
			phase++;
			timer[0] = 0;
			timer[1] = 0;
			timer[2] = 0;
			timer[3] = 0;
			timer[4] = 0;
			timer[5] = 0;
			timer[6] = 0;
			p_angle[1] = 0;
			p_angle[2] = 0;
			p_angle[3] = 0;
			p_angle[4] = 0;
			p_angle[5] = 0;
			p_angle[6] = 0;
		}
		break;
	case 5:
		for (int i = 0; i < 10; i++)
		{
			D3DXVec2Normalize(&direction, &(VECTOR2(WINSIZEX / 2, 180) - pos));
			pos += direction;
		}

		if (timer[0] >= 60)
		{
			phase++;
		}
		break;
	case 6:
		if (timer[1] % 24 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 30.f)
				OBJECT_M->Add(new bullet("enemy", -32, -32, 4.f, p_angle[1] + i, 0.5f, 10, TYPE::SPECIAL));
			p_angle[1] += 5.f;
		}
		timer[1]++;

		if (timer[2] % 24 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 30.f)
				OBJECT_M->Add(new bullet("enemy", -32, -32, 4.f, p_angle[2] + i, 0.5f, 10, TYPE::SPECIAL));
			p_angle[2] -= 5.f;
		}
		timer[2]++;

		if (timer[3] % 24 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 30.f)
				OBJECT_M->Add(new bullet("enemy", WINSIZEX + 32, -32, 4.f, p_angle[3] + i, 0.5f, 10, TYPE::SPECIAL));
			p_angle[3] += 5.f;
		}
		timer[3]++;

		if (timer[4] % 24 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 30.f)
				OBJECT_M->Add(new bullet("enemy", WINSIZEX + 32, -32, 4.f, p_angle[4] + i, 0.5f, 10, TYPE::SPECIAL));
			p_angle[4] -= 5.f;
		}
		timer[4]++;

		if (timer[5] % 24 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 30.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 4.f, p_angle[5] + i, 0.5f, 10, TYPE::SPECIAL));
			p_angle[5] += 5.f;
		}
		timer[5]++;

		if (timer[6] % 24 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 30.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 4.f, p_angle[6] + i, 0.5f, 10, TYPE::SPECIAL));
			p_angle[6] -= 5.f;
		}
		timer[6]++;

		if (hp <= 5000)
		{
			SOUND_M->Play("effect", false)->SetVolume(-1000);
			OBJECT_M->Add(new effect_2(pos.x, pos.y, 1.f, 90, VECTOR3(255, 0, 0)));
			OBJECT_M->Delete("bullet", "enemy");
			phase++;
			timer[0] = 0;
			angle = rand() % 360;
			direction = { cos(D3DXToRadian(angle)), sin(D3DXToRadian(angle)) };
			speed = 1;
		}
		break;
	case 7:
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

		pos += direction * speed;

		//collide
		if (collider.left < 0) direction.x = abs(direction.x);
		if (collider.right > WINSIZEX) direction.x = -abs(direction.x);
		if (collider.top < 0) direction.y = abs(direction.y);
		if (collider.bottom > 360) direction.y = -abs(direction.y);

		//pattern 1
		if (timer[2] % 60 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 15.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 3.f, p_angle[2] + i, 0.6f, 10, TYPE::SPECIAL));
			p_angle[2] += 3.f;
		}
		timer[2]++;

		//pattern 2
		if (timer[3] % 70 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 20.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 4.f, p_angle[3] + i, 0.7f, 10, TYPE::NORMAL));
			p_angle[3] += 6.f;
		}
		timer[3]++;

		//pattern 3
		if (timer[4] % 80 == 0)
		{
			for (float i = 0.f; i <= 360.f; i += 30.f)
				OBJECT_M->Add(new bullet("enemy", pos.x, pos.y, 5.f, p_angle[4] + i, 0.8f, 10, TYPE::NORMAL));
			p_angle[4] += 9.f;
		}
		timer[4]++;

		//pattern 4
		if (timer[5] >= 120)
		{
			if (timer[5] % 5 == 0)
			{
				VECTOR2 _direction;
				if (_player) D3DXVec2Normalize(&_direction, &(_player->pos -VECTOR2(-32, -32)));
				p_angle[5] = D3DXToDegree(atan2f(_direction.y, _direction.x));
				OBJECT_M->Add(new bullet("enemy", -32, -32, 12.f, p_angle[5], 0.65f, 15, TYPE::SPECIAL));

				if (_player) D3DXVec2Normalize(&_direction, &(_player->pos - VECTOR2(WINSIZEX + 32, -32)));
				p_angle[5] = D3DXToDegree(atan2f(_direction.y, _direction.x));
				OBJECT_M->Add(new bullet("enemy", WINSIZEX + 32, -32, 12.f, p_angle[5], 0.65f, 15, TYPE::SPECIAL));

				if (_player) D3DXVec2Normalize(&_direction, &(_player->pos - VECTOR2(-32, WINSIZEY + 32)));
				p_angle[5] = D3DXToDegree(atan2f(_direction.y, _direction.x));
				OBJECT_M->Add(new bullet("enemy", -32, WINSIZEY + 32, 12.f, p_angle[5], 0.65f, 15, TYPE::SPECIAL));

				if (_player) D3DXVec2Normalize(&_direction, &(_player->pos - VECTOR2(WINSIZEX + 32, WINSIZEY + 32)));
				p_angle[5] = D3DXToDegree(atan2f(_direction.y, _direction.x));
				OBJECT_M->Add(new bullet("enemy", WINSIZEX + 32, WINSIZEY + 32, 12.f, p_angle[5], 0.65f, 15, TYPE::SPECIAL));
			}

			if (timer[5] >= 135) timer[5] = 0;
		}
		timer[5]++;

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
		static_cast<game_system*>(OBJECT_M->Find("game_system"))->score += 50000;
		if (_player)
			static_cast<player*>(OBJECT_M->Find("player"))->exp += 400;
		Destroy();
	}
}

void boss_4::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("boss_4"), pos.x, pos.y, 0.6f, 1.f, 1.f, 90.f);
	//hp
	RENDER_M->Render(IMAGE_M->Find("hp"), 748, 20, 0.1f, hp / 25000.f, 1.f, 0.f, D3DCOLOR_RGBA(255, 0, 0, 255));
	RENDER_M->Render(IMAGE_M->Find("hp"), 748, 20, 0.15f, 1.f, 1.f, 0.f, D3DCOLOR_RGBA(64, 64, 64, 123));
}

void boss_4::Release()
{
	OBJECT_M->Add(new effect_2(pos.x, pos.y, 2.f, 120, VECTOR3(255, 0, 0)));
}