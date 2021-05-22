#include "DXUT.h"
#include "stage_1.h"

#include "game_system.h"
#include "player.h"

//enemy
#include "enemy_1.h"
#include "enemy_2.h"
#include "boss_1.h"
#include "boss_2.h"

void stage_1::Init()
{
	phase = 1;
	timer = 0;

	//reset
	OBJECT_M->Delete("enemy");
	OBJECT_M->Delete("bullet");
	OBJECT_M->Delete("effect");
	OBJECT_M->Delete("item");

	if (!OBJECT_M->Find("player"))
		OBJECT_M->Add(new player);

	SOUND_M->Stop();
	SOUND_M->Play("back_music", true)->SetVolume(-1500);
}

void stage_1::Update()
{
	switch (phase)
	{
	case 1://1-1 stage
		if (timer % 90 == 0 && timer <= 1200)
			OBJECT_M->Add(new enemy_1(rand() % 1120 + 80, -64, rand() % 90 + 45));
		if (timer > 1200 && OBJECT_M->FindList("enemy").size() <= 0)
		{
			phase++;
			timer = 0;
		}
		break;
	case 2://1-1 boss
		if (timer == 120)
			OBJECT_M->Add(new boss_1());
		if (timer > 120 && OBJECT_M->FindList("enemy").size() <= 0)
		{
			phase++;
			timer = 0;
		}
		break;
	case 3://1-2 stage
		if (timer % 90 == 0 && timer <= 1200)
			OBJECT_M->Add(new enemy_1(rand() % 1120 + 80, -64, rand() % 90 + 45));
		if (timer % 120 == 0 && timer <= 1200)
			OBJECT_M->Add(new enemy_2(rand() % 1120 + 80, -64, rand() % 90 + 45));
		if (timer > 1200 && OBJECT_M->FindList("enemy").size() <= 0)
		{
			phase++;
			timer = 0;
		}
		break;
	case 4://1-2 boss
		if (timer == 120)
			OBJECT_M->Add(new boss_2());
		if (timer > 120 && OBJECT_M->FindList("enemy").size() <= 0)
		{
			SOUND_M->Stop();
			SOUND_M->Play("win", false)->SetVolume(-1000);
			SCENE_M->Change("rank_1"); 
		}
		break;
	}
	timer++;

	game_system* _system = static_cast<game_system*>(OBJECT_M->Find("game_system"));

	//background
	if ((phase == 2 || phase == 4) && _system->scroll_speed > 0.f) _system->scroll_speed -= 0.05f;
	else if (_system->scroll_speed < 5.f) _system->scroll_speed += 0.05f;
	if (_system->background_red < 255) _system->background_red++;
	if (_system->background_black < 255) _system->background_black++;
}

void stage_1::Render()
{
}

void stage_1::Release()
{

}
