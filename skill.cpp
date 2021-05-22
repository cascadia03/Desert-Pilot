#include "DXUT.h"
#include "skill.h"

#include "bullet.h"
#include "enemy.h"
#include "player.h"

//shield
void shield::Init()
{
	timer = 180;
	SOUND_M->Play("effect", false)->SetVolume(-1000);
}

void shield::Update()
{
	if (timer <= 0) Destroy();
	else timer--;

	player* _player = static_cast<player*>(OBJECT_M->Find("player"));

	RECT temp;
	for (auto i : OBJECT_M->FindList("bullet", "enemy"))
		if (IntersectRect(&temp, &collider, &static_cast<bullet*>(i)->collider))
		{
			if (_player)
			{
				if (_player->level >= 5)
				{
					i->tag = "player";
					static_cast<bullet*>(i)->angle = 270.f;
				}
				else i->Destroy();
			}
		}

	SetRect(&collider, pos->x - 24, pos->y - 24, pos->x + 24, pos->y + 24);
}

void shield::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("effect"), pos->x, pos->y, 0.4f, 0.1f, 0.1f, 0.f, D3DCOLOR_RGBA(64, 64, 255, 181));
}

void shield::Release()
{
}

//bomb
void bomb::Init()
{
	SOUND_M->Play("effect", false)->SetVolume(-1000);
	for (auto i : OBJECT_M->FindList("bullet", "enemy"))
		i->Destroy();
	for (auto i : OBJECT_M->FindList("enemy"))
		static_cast<enemy*>(i)->hp -= static_cast<player*>(OBJECT_M->Find("player"))->atk * 5;
	timer = 60;
}

void bomb::Update()
{
	if (timer <= 0) Destroy();
	else timer--;
}

void bomb::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("effect"), pos.x, pos.y, 0.2f, (60.f - timer) / 30.f, (60.f - timer) / 30.f, 0.f, D3DCOLOR_RGBA(255, 255, 255, (int)(255 * (timer / 60.f))));
}

void bomb::Release()
{
}

//levelup
void levelup::Init()
{
	SOUND_M->Play("effect", false)->SetVolume(-1000);
	timer = 60;
}

void levelup::Update()
{
	if (timer <= 0) Destroy();
	else timer--;
}

void levelup::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("effect"), pos.x, pos.y, 0.2f, (60.f - timer) / 30.f, (60.f - timer) / 30.f, 0.f, D3DCOLOR_RGBA(64, 255, 64, (int)(255 * (timer / 60.f))));
}

void levelup::Release()
{
}
