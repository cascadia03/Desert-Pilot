#include "DXUT.h"
#include "bullet.h"

#include "player.h"
#include "enemy.h"
#include "effect.h"

void bullet::Init()
{
	if (tag == "player")
		if (b_type == SPECIAL)
			SOUND_M->Play("bomb_3", false)->SetVolume(-2000);
		else if (b_type == NORMAL)
			SOUND_M->Play("bomb_3", false)->SetVolume(-3000);
}

void bullet::Update()
{
	//direction
	direction = { cos(D3DXToRadian(angle)), sin(D3DXToRadian(angle)) };

	//movement
	pos += direction * speed;
	
	//collider
	SetRect(&collider, pos.x - 16 * size, pos.y - 16 * size, pos.x + 16 * size, pos.y + 16 * size);

	//IsOut
	if (collider.left < -48 || collider.right > WINSIZEX + 48 ||
		collider.top < -48 || collider.bottom > WINSIZEY + 48) Destroy();

	RECT temp;
	//playar
	if (tag == "player")
	{
		for (auto i : OBJECT_M->FindList("enemy"))
		{
			enemy* _enemy = static_cast<enemy*>(i);
			if (IntersectRect(&temp, &collider, &_enemy->collider))
			{
				SOUND_M->Play("bomb_2", false)->SetVolume(-2000);
				_enemy->hp -= damage;
				Destroy();
			}
		}
	}
	//enemy
	if (tag == "enemy")
	{
		player* _player = static_cast<player*>(OBJECT_M->Find("player"));
		if (_player)
		{
			if (IntersectRect(&temp, &collider, &_player->collider))
			{
				SOUND_M->Play("bomb_2", false)->SetVolume(-2000);
				_player->hp -= damage;
				Destroy();
			}
		}
	}
}

void bullet::Render()
{
	D3DCOLOR color;

	if (tag == "player")
		color = D3DCOLOR_RGBA(0, 0, 255, 182);
	if (tag == "enemy")
		color = D3DCOLOR_RGBA(255, 0, 0, 182);

	switch (b_type)
	{
	case NORMAL:
		RENDER_M->CenterRender(IMAGE_M->Find("normal_b"), pos.x, pos.y, 0.3f, size, size, angle, color);
		break;
	case SPECIAL:
		RENDER_M->CenterRender(IMAGE_M->Find("special_b"), pos.x, pos.y, 0.3f, size, size, angle, color);
		break;
	}
}

void bullet::Release()
{
	OBJECT_M->Add(new effect_1(pos.x + rand() % 16 - 8, pos.y + rand() % 16 - 8, rand() % 5 * 0.1 + 0.5, rand() % 15 + 15, VECTOR3(255, 255, 255)));
}
