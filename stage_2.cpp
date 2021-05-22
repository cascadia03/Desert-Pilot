#include "DXUT.h"
#include "stage_2.h"

#include "game_system.h"
#include "player.h"

//enemy
#include "enemy_1.h"
#include "enemy_2.h"
#include "enemy_3.h"
#include "enemy_4.h"
#include "boss_3.h"
#include "boss_4.h"

void stage_2::Init()
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

void stage_2::Update()
{
	game_system* _system = static_cast<game_system*>(OBJECT_M->Find("game_system"));

	switch (phase)
	{
	case 1://2-1 stage
		if (timer % 90 == 0 && timer <= 1200)
			OBJECT_M->Add(new enemy_1(rand() % 1120 + 80, -64, rand() % 90 + 45));
		if (timer % 120 == 0 && timer <= 1200)
			OBJECT_M->Add(new enemy_2(rand() % 1120 + 80, -64, rand() % 90 + 45));
		if (timer % 240 == 0 && timer <= 1200)
			OBJECT_M->Add(new enemy_3(rand() % 1120 + 80, -64));
		if (timer > 1200 && OBJECT_M->FindList("enemy").size() <= 0)
		{
			phase++;
			timer = 0;
		}
		break;
	case 2://2-1 boss
		if (timer == 120)
			OBJECT_M->Add(new boss_3());
		if (timer > 120 && OBJECT_M->FindList("enemy").size() <= 0)
		{
			phase++;
			timer = 0;
		}
		break;
	case 3://2-2 stage
		if (timer % 90 == 0 && timer <= 1200)
			OBJECT_M->Add(new enemy_1(rand() % 1120 + 80, -64, rand() % 90 + 45));
		if (timer % 120 == 0 && timer <= 1200)
			OBJECT_M->Add(new enemy_2(rand() % 1120 + 80, -64, rand() % 90 + 45));
		if (timer % 240 == 0 && timer <= 1200)
			OBJECT_M->Add(new enemy_3(rand() % 1120 + 80, -64));
		if (timer % 360 == 0 && timer <= 1200)
			OBJECT_M->Add(new enemy_4(rand() % 1120 + 80, -64, rand() % 90 + 45));
		if (timer > 1200 && OBJECT_M->FindList("enemy").size() <= 0)
		{
			phase++;
			timer = 0;
		}
		break;
	case 4://2-2 boss
		if (_system->background_black > 0)_system->background_black--;
		if (_system->background_red > 0) _system->background_red--;

		if (timer == 120)
			OBJECT_M->Add(new boss_4());
		if (timer > 120 && OBJECT_M->FindList("enemy").size() <= 0)
		{
			SOUND_M->Stop();
			SOUND_M->Play("win", false)->SetVolume(-1000);
			SCENE_M->Change("rank_2");
		}
		break;
	}
	timer++;

	//background
	if ((phase == 2 || phase == 4) && _system->scroll_speed > 0.f) _system->scroll_speed -= 0.05f;
	else if (_system->scroll_speed < 5.f) _system->scroll_speed += 0.05f;
	if (_system->background_red > 185) _system->background_red--;
	if (_system->background_black < 255 && phase != 4) _system->background_black++;
}

void stage_2::Render()
{
}

void stage_2::Release()
{

}
