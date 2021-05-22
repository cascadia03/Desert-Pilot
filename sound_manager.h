#pragma once
#include "singleton.h"

class sound_manager : public singleton<sound_manager>
{
private:
	CSoundManager manager;
	map<string, CSound*> sounds;
	list<LPDIRECTSOUNDBUFFER> channels;
public:
	sound_manager();
	~sound_manager();

	void Update();
	
	void Add(string _key, wstring _path);
	void Stop();
	LPDIRECTSOUNDBUFFER Play(string _key, bool _loop);
};

#define SOUND_M sound_manager::GetInst()