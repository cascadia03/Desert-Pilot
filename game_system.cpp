#include "DXUT.h"
#include "game_system.h"

#include "player.h"
#include "item.h"
#include "enemy.h"

void game_system::Init()
{
	//score
	for (auto& i : ranked_name)
		i = "NON";
	for (auto& i : ranked_score)
		i = 0;
	score = 0;

	//error
	skill_error = 0;

	//cheat
	showStat = false;

	//background
	background_red = 255;
	background_black = 255;
	background_y = 0;
	scroll_speed = 1.f;
}

void game_system::Update()
{
	//cheat
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));
	if (INPUT_M->Pressed(VK_F1)) //player overpowered
		if (_player) _player->IsOverpowered = !_player->IsOverpowered;
	if (INPUT_M->Pressed(VK_F2)) //player levelup
		if (_player) _player->exp = _player->max_exp;
	if (INPUT_M->Pressed(VK_F3)) //create a item;
		if (_player)
			switch (rand() % 3)
			{
			case 0:
				OBJECT_M->Add(new levelupgrade(_player->pos.x, 120));
				break;
			case 1:
				OBJECT_M->Add(new cooltimeReset(_player->pos.x, 120));
				break;
			case 2:
				OBJECT_M->Add(new Healkit(_player->pos.x, 120));
				break;
			}
	if (INPUT_M->Pressed(VK_F4)) //change scene to main menu
		SCENE_M->Change("main_menu");
	if (INPUT_M->Pressed(VK_F5)) //change scene to stage 1
		SCENE_M->Change("stage_1");
	if (INPUT_M->Pressed(VK_F6)) //change scene to stage 2
		SCENE_M->Change("stage_2");
	if (INPUT_M->Pressed(VK_F7)) //show player stat
		showStat = !showStat;

	//error
	if (skill_error > 0) skill_error--;

	//background
	if (background_y >= 1360) background_y = 0;
	else background_y += scroll_speed;
}

void game_system::Render()
{
	//background
	RENDER_M->Render(IMAGE_M->Find("bg_desert"), 0, background_y, 1.f, 1.f, 1.f, 0.f, D3DCOLOR_RGBA(background_black, background_red, background_red, 255));
	RENDER_M->Render(IMAGE_M->Find("bg_desert"), 0, background_y - 1360, 1.f, 1.f, 1.f, 0.f, D3DCOLOR_RGBA(background_black, background_red, background_red, 255));

	//player
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));
	if (_player)
	{
		//hp
		RENDER_M->Render(IMAGE_M->Find("hp"), 20, 668, 0.1f, (float)_player->hp / _player->max_hp, 1.f, 0.f, D3DCOLOR_RGBA(0, 0, 255, 255));
		RENDER_M->Render(IMAGE_M->Find("hp"), 20, 668, 0.15f, 1.f, 1.f, 0.f, D3DCOLOR_RGBA(64, 64, 64, 123));
		//exp
		RENDER_M->Render(IMAGE_M->Find("hp"), 20, 638, 0.1f, (float)_player->exp / _player->max_exp, 0.5f, 0.f, D3DCOLOR_RGBA(0, 181, 0, 255));
		RENDER_M->Render(IMAGE_M->Find("hp"), 20, 638, 0.15f, 1.f, 0.5f, 0.f, D3DCOLOR_RGBA(64, 64, 64, 123));
		//shield_cooltime
		RENDER_M->Render(IMAGE_M->Find("shield_icon"), 1116, 638, 0.1f);
		RENDER_M->Render(IMAGE_M->Find("cooltime"), 1116, 638, 0.1f, 1.f, (600.f - _player->shield_cooltimer) / 600.f);
		//bomb_cooltime
		RENDER_M->Render(IMAGE_M->Find("bomb_icon"), 1196, 638, 0.1f);
		RENDER_M->Render(IMAGE_M->Find("cooltime"), 1196, 638, 0.1f, 1.f, (1800.f - _player->bomb_cooltimer) / 1800.f);
		//level
		RENDER_M->RenderText("LEVEL" + to_string(_player->level), 20, 588, 0.1f, 50.f);
		//score
		RENDER_M->RenderText("SCORE " + to_string(score), 20, 20, 0.1f, 40.f);

		//stat
		if (showStat)
		{
			RENDER_M->RenderText(to_string(_player->hp) + "/" + to_string(_player->max_hp), 25, 668, 0.05f, 30.f);
			RENDER_M->RenderText(to_string(_player->exp) + "/" + to_string(_player->max_exp), 25, 638, 0.05f, 20.f);
		}

		//skill_error
		RENDER_M->RenderText("아직 사용할 수 없습니다", 880, 580, 0.1f, 30.f, 0.f, D3DCOLOR_RGBA(255, 255, 255, (int)(255 * (skill_error / 100.f))));
	}
}

void game_system::Release()
{
}

void game_system::rankUpdate(string _name)
{
	for (int i = 0; i < 5; i++)
	{
		if (ranked_score[0] < score)
		{
			for (int j = 4; j > i; j--)
			{
				ranked_score[j] = ranked_score[j - 1];
				ranked_name[j] = ranked_name[j - 1];
			}
			ranked_score[i] = score;
			ranked_name[i] = _name;
			score = 0;
			break;
		}
	}
}
