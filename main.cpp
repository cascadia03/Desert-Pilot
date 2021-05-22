#include "DXUT.h"
#include "main.h"

#include "setting.h"
#include "main_menu.h"
#include "stage_1.h"
#include "stage_2.h"
#include "rank_1.h"
#include "rank_2.h"

void main::Init()
{
	SCENE_M->Add("setting", new setting());
	SCENE_M->Add("main_menu", new main_menu());
	SCENE_M->Add("stage_1", new stage_1());
	SCENE_M->Add("stage_2", new stage_2());
	SCENE_M->Add("rank_1", new rank_1());
	SCENE_M->Add("rank_2", new rank_2());

	SCENE_M->Change("setting");
}

void main::Update()
{
	SCENE_M->Update();
	OBJECT_M->Update();
	SOUND_M->Update();
	INPUT_M->Update();
}

void main::Render()
{
	RENDER_M->Begin();
	SCENE_M->Render();
	OBJECT_M->Render();
	RENDER_M->End();
}

void main::Release()
{
	image_manager::ReleaseInst();
	input_manager::ReleaseInst();
	scene_manager::ReleaseInst();
	object_manager::ReleaseInst();
	render_manager::ReleaseInst();
	sound_manager::ReleaseInst();
}

void main::LostDevice()
{
	RENDER_M->LostDevice();
}

void main::ResetDevice()
{
	RENDER_M->ResetDevice();
}
