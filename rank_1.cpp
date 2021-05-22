#include "DXUT.h"
#include "rank_1.h"

#include "game_system.h"
#include "player.h"

void rank_1::Init()
{
	//reset
	OBJECT_M->Delete("enemy");
	OBJECT_M->Delete("bullet");
	OBJECT_M->Delete("item");

	game_system* _system = static_cast<game_system*>(OBJECT_M->Find("game_system"));
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));
	if (_player)
		_system->score += max(_player->hp * 10000, 0);

	timer = 0;
}

void rank_1::Update()
{
	timer++;
	if (timer >= 120)
	{
		if (INPUT_M->Pressed(VK_RETURN))
		{
			SOUND_M->Play("button_1", false)->SetVolume(-1000);
			SCENE_M->Change("stage_2");
		}
	}
}

void rank_1::Render()
{
	game_system* _system = static_cast<game_system*>(OBJECT_M->Find("game_system"));
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));
	
	if (_player)
	{
		RENDER_M->RenderText("YOU WIN!", 400, 120, 0.1f, 60.f);
		RENDER_M->RenderText("LIFE SCORE " + to_string(_player->hp * 1000), 360, 280, 0.1f, 60.f);
	}
	RENDER_M->RenderText("TOTAL SCORE " + to_string(_system->score), 360, 360, 0.1f, 60.f);
	if (timer >= 120)
		RENDER_M->RenderText("ENTER를 눌러 다음 스테이지로 이동", 360, 440, 0.1f, 30.f);

	//background
	if (_system->scroll_speed < 5.f) _system->scroll_speed += 0.05f;
}

void rank_1::Release()
{
	player* _player = static_cast<player*>(OBJECT_M->Find("player"));
	if (_player)
		_player->hp = _player->max_hp;
}
