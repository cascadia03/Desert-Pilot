#pragma once
#include "singleton.h"

class texture;

class render_manager : public singleton<render_manager>
{
private:
	LPD3DXSPRITE sprite;
	LPD3DXFONT font;
public:
	render_manager();
	~render_manager();

	void Render(texture* _image, float _x, float _y, float _depth, float _sizex = 1.f, float _sizey = 1.f, float _angle = 0.f, D3DCOLOR _color = D3DCOLOR_RGBA(255, 255, 255, 255));
	void CenterRender(texture* _image, float _x, float _y, float _depth, float _sizex = 1.f, float _sizey = 1.f, float _angle = 0.f, D3DCOLOR _color = D3DCOLOR_RGBA(255, 255, 255, 255));
	void RenderText(string _text, float _x, float _y, float _depth, float _size = 1.f, float _angle = 0.f, D3DCOLOR _color = D3DCOLOR_RGBA(255, 255, 255, 255));
	void CenterRenderText(string _text, float _x, float _y, float _depth, float _size = 1.f, float _angle = 0.f, D3DCOLOR _color = D3DCOLOR_RGBA(255, 255, 255, 255));
	
	void Begin();
	void End();
	void LostDevice();
	void ResetDevice();
};

#define RENDER_M render_manager::GetInst()