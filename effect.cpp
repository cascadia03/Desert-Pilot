#include "DXUT.h"
#include "effect.h"

//effect_!
void effect_1::Init()
{
	cooltimer = 0;
}

void effect_1::Update()
{
	if (cooltimer >= timer) Destroy();
	else cooltimer++;
}

void effect_1::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("normal_b"), pos.x, pos.y, 0.2f, size, size, rand() % 360, D3DCOLOR_RGBA((int)color.x, (int)color.y, (int)color.z, (int)(165 * ((float)(timer - cooltimer) / timer))));
}

void effect_1::Release()
{
}

//effect_2
void effect_2::Init()
{
	cooltimer = 0;
}

void effect_2::Update()
{
	if (cooltimer >= timer) Destroy();
	else cooltimer++;
}

void effect_2::Render()
{
	RENDER_M->CenterRender(IMAGE_M->Find("effect"), pos.x, pos.y, 0.2f, size * cooltimer / timer, size * cooltimer / timer, rand() % 360, D3DCOLOR_RGBA((int)color.x, (int)color.y, (int)color.z, (int)(255 * ((float)(timer - cooltimer) / timer))));
}

void effect_2::Release()
{
}
