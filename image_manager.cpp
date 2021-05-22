#include "DXUT.h"
#include "image_manager.h"

image_manager::image_manager()
{
}

image_manager::~image_manager()
{
	for (auto i : images)
	{
		SAFE_RELEASE(i.second->image);
		SAFE_DELETE(i.second);
	}
	images.clear();
}

void image_manager::Add(string _key, string _path)
{
	LPDIRECT3DTEXTURE9 image;
	D3DXIMAGE_INFO info;
	if (D3DXCreateTextureFromFileExA(g_device, _path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &image) == S_OK)
		images[_key] = new texture(image, info);
	else SAFE_DELETE(image);
}

texture* image_manager::Find(string _key)
{
	return images[_key];
}
