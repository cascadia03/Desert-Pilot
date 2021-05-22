#include "DXUT.h"
#include "render_manager.h"

render_manager::render_manager()
{
	D3DXCreateSprite(g_device, &sprite);
}

render_manager::~render_manager()
{
	SAFE_RELEASE(sprite);
}

void render_manager::Render(texture * _image, float _x, float _y, float _depth, float _sizex, float _sizey, float _angle, D3DCOLOR _color)
{
	D3DXMATRIXA16 matrix, scale, rotation, translation;
	D3DXMatrixScaling(&scale, _sizex, _sizey, 1.f);
	D3DXMatrixRotationZ(&rotation, D3DXToRadian(_angle));
	D3DXMatrixTranslation(&translation, _x, _y, 0.f);

	matrix = scale * rotation * translation;
	matrix._43 = _depth;

	sprite->SetTransform(&matrix);
	sprite->Draw(_image->image, nullptr, &VECTOR3(0.f, 0.f, 0.f), nullptr, _color);
}

void render_manager::CenterRender(texture * _image, float _x, float _y, float _depth, float _sizex, float _sizey, float _angle, D3DCOLOR _color)
{
	D3DXMATRIXA16 matrix, scale, rotation, translation;
	D3DXMatrixScaling(&scale, _sizex, _sizey, 1.f);
	D3DXMatrixRotationZ(&rotation, D3DXToRadian(_angle));
	D3DXMatrixTranslation(&translation, _x, _y, 0.f);

	matrix = scale * rotation * translation;
	matrix._43 = _depth;

	sprite->SetTransform(&matrix);
	sprite->Draw(_image->image, nullptr, &VECTOR3(_image->info.Width / 2, _image->info.Height / 2, 0.f), nullptr, _color);
}

void render_manager::RenderText(string _text, float _x, float _y, float _depth, float _size, float _angle, D3DCOLOR _color)
{
	D3DXMATRIXA16 matrix;
	D3DXCreateFontA(g_device, _size, 0, 0, 1, FALSE, HANGEUL_CHARSET, 0, 0, 0, "Fixedsys", &font);
	D3DXMatrixTranslation(&matrix, _x, _y, 0.f);
	matrix._43 = _depth;

	sprite->SetTransform(&matrix);
	font->DrawTextA(sprite, _text.c_str(), _text.size(), nullptr, DT_NOCLIP, _color);
	SAFE_RELEASE(font);
}

void render_manager::CenterRenderText(string _text, float _x, float _y, float _depth, float _size, float _angle, D3DCOLOR _color)
{
	D3DXMATRIXA16 matrix;
	D3DXCreateFontA(g_device, _size, 0, 0, 1, FALSE, HANGEUL_CHARSET, 0, 0, 0, "Fixedsys", &font);
	D3DXMatrixTranslation(&matrix, _x - _size * _text.size() * 0.25f, _y - _size * 0.5f, 0.f);
	matrix._43 = _depth;

	sprite->SetTransform(&matrix);
	font->DrawTextA(sprite, _text.c_str(), _text.size(), nullptr, DT_NOCLIP, _color);
	SAFE_RELEASE(font);
}

void render_manager::Begin()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
}

void render_manager::End()
{
	sprite->End();
}

void render_manager::LostDevice()
{
	sprite->OnLostDevice();
}

void render_manager::ResetDevice()
{
	sprite->OnResetDevice();
}
