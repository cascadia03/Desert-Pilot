#include "DXUT.h"
#include "player.h"

#include "game_system.h"
#include "bullet.h"
#include "skill.h"

void player::Init()
{
	pos = { WINSIZEX / 2, WINSIZEY + 64 };
	collider = { 0, 0, 0, 0 };

	//stat
	level = 1;
	exp = 0;
	max_exp = 100;
	hp = 100;
	max_hp = 100;
	speed = 8;
	atk = 15;
	atk_speed = 1;

	//appear
	IsAppear = false;

	//shooting
	weapon_type = 0;
	shot_cooltimer = 0;

	//shield
	shield_cooltimer = 0;

	//bomb
	bomb_cooltimer = 0;
	bomb_timer = 0;

	//cheat
	IsOverpowered = false;
}

void player::Update()
{
	if (!IsAppear)//before appear
	{
		pos.y -= 4.f;
		if (pos.y < 560) IsAppear = true;
	}
	else//after appear
	{
		//movement
		float _speed;
		if (INPUT_M->Pressing(VK_SHIFT)) _speed = speed / 2;
		else _speed = speed;
		if (INPUT_M->Pressing(VK_LEFT) && pos.x > 0) pos.x -= _speed;
		if (INPUT_M->Pressing(VK_RIGHT) && pos.x < WINSIZEX) pos.x += _speed;
		if (INPUT_M->Pressing(VK_UP) && pos.y > 0) pos.y -= _speed;
		if (INPUT_M->Pressing(VK_DOWN) && pos.y < WINSIZEY) pos.y += _speed;

		//shooting
		if (INPUT_M->Pressing('Z'))
		{
			if (weapon_type == 0 && shot_cooltimer >= 10 * atk_speed)
			{
				OBJECT_M->Add(new bullet("player", pos.x, pos.y - 18, 15.f, 270.f, 0.5f, atk, TYPE::SPECIAL));
				shot_cooltimer = 0;
			}
			if (weapon_type == 1 && shot_cooltimer >= 20 * atk_speed)
			{
				for (float i = 0.f; i <= 40.f; i += 10.f)
					OBJECT_M->Add(new bullet("player", pos.x, pos.y - 18, 10.f, 250 + i, 0.5f, atk * 0.75, TYPE::NORMAL));
				shot_cooltimer = 0;
			}
		}
		shot_cooltimer++;
		if (INPUT_M->Pressed('X')) weapon_type = !weapon_type;

		//shield
		if (INPUT_M->Pressed('A'))
		{
			if (shield_cooltimer >= 600)
			{
				OBJECT_M->Add(new shield(&pos));
				shield_cooltimer = 0;
			}
			else static_cast<game_system*>(OBJECT_M->Find("game_system"))->skill_error = 100;
		}
		if (shield_cooltimer < 600 && level >= 3) shield_cooltimer++;

		//bomb
		if (INPUT_M->Pressed('S'))
		{
			if (bomb_cooltimer >= 1800)
			{
				bomb_timer = 180;
				bomb_cooltimer = 0;
			}
			else static_cast<game_system*>(OBJECT_M->Find("game_system"))->skill_error = 100;
		}
		if (bomb_cooltimer < 1800 && level >= 5) bomb_cooltimer++;
		if (bomb_timer > 0)
		{
			if (bomb_timer % 60 == 0) 
				OBJECT_M->Add(new bomb(pos));
			bomb_timer--;
		}

		//levelup
		if (exp >= max_exp && level < 5)
		{
			OBJECT_M->Add(new levelup(pos));
			level++;
			exp -= max_exp;
			max_exp += 100;
			hp = max_hp *= 1.2;
			atk *= 1.2;
			atk_speed *= 0.8;
			if (level == 3) shield_cooltimer = 600;
			if (level == 5) bomb_cooltimer = 1800;
		}
		if (level >= 5) exp = max_exp;
		if (level < 3) shield_cooltimer = 0;
		if (level < 5) bomb_cooltimer = 0;

		//game over
		if (hp <= 0)
		{
			Destroy();
			SOUND_M->Stop();
			SOUND_M->Play("lose", false)->SetVolume(-1000);
			SCENE_M->Change("rank_2");
		}
		if (hp > max_hp) hp = max_hp;
	}

	//collider
	if (IsOverpowered) SetRect(&collider, - 256, - 256, - 256, - 256);
	else SetRect(&collider, pos.x - 4, pos.y - 4, pos.x + 4, pos.y + 4);
}

void player::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("player"), pos.x, pos.y, 0.5f, 1.f, 1.f, 270.f);
}

void player::Release()
{
}
