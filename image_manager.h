#pragma once
#include "singleton.h"

class texture
{
public:
	LPDIRECT3DTEXTURE9 image;
	D3DXIMAGE_INFO info;

	texture(LPDIRECT3DTEXTURE9 _image, D3DXIMAGE_INFO _info) : image(_image), info(_info) {}
	~texture() {}
};

class image_manager : public singleton<image_manager>
{
private:
	map<string, texture*> images;
public:
	image_manager();
	~image_manager();

	void Add(string _key, string _path);
	texture* Find(string _key);
};

#define IMAGE_M image_manager::GetInst()