#include "DXUT.h"
#include "sound_manager.h"

sound_manager::sound_manager()
{
	manager.Initialize(DXUTGetHWND(), 1);
}

sound_manager::~sound_manager()
{
	for (auto& i : sounds)
		SAFE_DELETE(i.second);
	sounds.clear();

	for (auto& i : channels)
		SAFE_RELEASE(i);
	channels.clear();
}

void sound_manager::Update()
{
	DWORD status;
	for (auto i = channels.begin(); i != channels.end();)
	{
		(*i)->GetStatus(&status);
		if (!status & !DSBSTATUS_PLAYING)
		{
			SAFE_RELEASE(*i);
			i = channels.erase(i);
		}
		else i++;
	}
}

void sound_manager::Add(string _key, wstring _path)
{
	CSound** sound = new CSound*();
	wchar_t w_path[256];
	swprintf(w_path, L"%s", _path.c_str());
	manager.Create(sound, w_path, DSBCAPS_CTRLVOLUME);
	sounds[_key] = *sound;
	SAFE_DELETE(sound);
}

void sound_manager::Stop()
{
	for (auto& i : channels)
		SAFE_RELEASE(i);
	channels.clear();
}

LPDIRECTSOUNDBUFFER sound_manager::Play(string _key, bool _loop)
{
	LPDIRECTSOUNDBUFFER buffer;
	manager.GetDirectSound()->DuplicateSoundBuffer(sounds[_key]->GetBuffer(0), &buffer);
	buffer->Play(0, 0, _loop ? DSBPLAY_LOOPING : 0);
	channels.push_back(buffer);
	return buffer;
}
