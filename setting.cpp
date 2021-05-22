#include "DXUT.h"
#include "setting.h"

#include "game_system.h"

void setting::Init()
{
	//system
	OBJECT_M->Add(new game_system());

	//main menu
	IMAGE_M->Add("m_title", "./images/main_menu/title.png");
	IMAGE_M->Add("m_start", "./images/main_menu/start.png");
	IMAGE_M->Add("m_info", "./images/main_menu/info.png");
	IMAGE_M->Add("m_rank", "./images/main_menu/rank.png");
	IMAGE_M->Add("m_exit", "./images/main_menu/exit.png");
	IMAGE_M->Add("m_detailed_info", "./images/main_menu/detailed_info.png");
	IMAGE_M->Add("m_detailed_rank", "./images/main_menu/detailed_rank.png");

	//background
	IMAGE_M->Add("bg_desert", "./images/background.png");

	//player
	IMAGE_M->Add("player", "./images/player.png");

	//RGB_resource
	IMAGE_M->Add("normal_b", "./images/RGB_resource/normal_b.png");
	IMAGE_M->Add("special_b", "./images/RGB_resource/special_b.png");
	IMAGE_M->Add("effect", "./images/RGB_resource/effect.png");
	IMAGE_M->Add("hp", "./images/RGB_resource/hp.png");

	//skill icon
	IMAGE_M->Add("shield_icon", "./images/skill_icon/shield.png");
	IMAGE_M->Add("bomb_icon", "./images/skill_icon/bomb.png");
	IMAGE_M->Add("cooltime", "./images/skill_icon/cooltime.png");

	//item
	IMAGE_M->Add("cooltimeReset", "./images/item/cooltime.png");
	IMAGE_M->Add("healkit", "./images/item/healkit.png");
	IMAGE_M->Add("levelup", "./images/item/levelup.png");

	//enemy
	IMAGE_M->Add("enemy_1", "./images/enemy/1.png");
	IMAGE_M->Add("enemy_2", "./images/enemy/2.png");
	IMAGE_M->Add("enemy_3", "./images/enemy/3.png");
	IMAGE_M->Add("enemy_4", "./images/enemy/4.png");
	IMAGE_M->Add("boss_1", "./images/enemy/boss_1.png");
	IMAGE_M->Add("boss_2", "./images/enemy/boss_2.png");
	IMAGE_M->Add("boss_3", "./images/enemy/boss_3.png");
	IMAGE_M->Add("boss_4", "./images/enemy/boss_4.png");

	//sound
	SOUND_M->Add("button_1", L"./sounds/Back Button.wav");
	SOUND_M->Add("button_2", L"./sounds/Menu Button.wav");
	SOUND_M->Add("boss_appear", L"./sounds/Driving Loop.wav");
	SOUND_M->Add("back_music", L"./sounds/Main Music 9000.wav");
	SOUND_M->Add("bomb_1", L"./sounds/bomb_1.wav");
	SOUND_M->Add("bomb_2", L"./sounds/bomb_2.wav");
	SOUND_M->Add("bomb_3", L"./sounds/bomb_3.wav");
	SOUND_M->Add("win", L"./sounds/win.wav");
	SOUND_M->Add("lose", L"./sounds/lose.wav");
	SOUND_M->Add("effect", L"./sounds/TD Tower Upgrade.wav");
}

void setting::Update()
{
	SCENE_M->Change("main_menu");
}

void setting::Render()
{
}

void setting::Release()
{
}
