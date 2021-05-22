#include "DXUT.h"
#include "rank_2.h"

#include "game_system.h"
#include "player.h"

void rank_2::Init()
{
	//reset
	OBJECT_M->Delete("enemy");
	OBJECT_M->Delete("bullet");
	OBJECT_M->Delete("item");

	game_system* _system = static_cast<game_system*>(OBJECT_M->Find("game_system"));
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));
	if (_player)
		_system->score += max(_player->hp * 1000, 0);

	initial = "";
	timer = 0;
}

void rank_2::Update()
{
	game_system* _system = static_cast<game_system*>(OBJECT_M->Find("game_system"));

	timer++;
	if (timer >= 120)
	{
		for (int i = 0; i < 256; i++)
			if (INPUT_M->Pressed(i) && initial.size() < 3 && i != VK_RETURN && i != VK_BACK)
			{
				SOUND_M->Play("button_1", false)->SetVolume(-1000);
				initial.push_back(i);
			}
		if (INPUT_M->Pressed(VK_BACK) && initial.size() > 0)
		{
			SOUND_M->Play("button_1", false)->SetVolume(-1000);
			initial.pop_back();
		}

		if (INPUT_M->Pressed(VK_RETURN) && initial.size() >= 3)
		{
			SOUND_M->Play("button_1", false)->SetVolume(-1000);
			_system->rankUpdate(initial);
			SCENE_M->Change("main_menu");
		}
	}

	//background
	if (_system->scroll_speed < 5.f) _system->scroll_speed += 0.05f;
}

void rank_2::Render()
{
	game_system* _system = static_cast<game_system*>(OBJECT_M->Find("game_system"));
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));

	if (_player)
	{
		RENDER_M->RenderText("YOU WIN!", 400, 120, 0.1f, 60.f);
		RENDER_M->RenderText("LIFE SCORE " + to_string(_player->hp * 1000), 360, 280, 0.1f, 60.f);
	}
	else RENDER_M->RenderText("YOU LOSE...", 400, 120, 0.1f, 60.f);
	RENDER_M->RenderText("TOTAL SCORE " + to_string(_system->score), 360, 360, 0.1f, 60.f);
	if (timer >= 120)
	{
		RENDER_M->RenderText(initial, 560, 180, 0.1f, 100.f);
		RENDER_M->RenderText("___", 560, 180, 0.1f, 100.f);
		RENDER_M->RenderText("이니셜을 입력하고 ENTER를 눌러 메인화면으로", 300, 440, 0.1f, 30.f);
	}
}

void rank_2::Release()
{
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));
	if (_player)
		_player->hp = _player->max_hp;
}
