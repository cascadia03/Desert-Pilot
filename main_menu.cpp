#include "DXUT.h"
#include "main_menu.h"

#include "game_system.h"

void main_menu::Init()
{
	phase = 0;

	//reset
	OBJECT_M->Delete("player");
	OBJECT_M->Delete("enemy");
	OBJECT_M->Delete("bullet");
	OBJECT_M->Delete("effect");
	OBJECT_M->Delete("item");

	//title
	t_pos = {WINSIZEX / 2, WINSIZEY / 2};
	t_alpha = 0;

	SOUND_M->Stop();

	//menu
	selection = 0;
	for (auto i : m_alpha) i = 0;
	for (auto i : m_size) i = 0.f;
}

void main_menu::Update()
{
	game_system* _system = static_cast<game_system*>(OBJECT_M->Find("game_system"));

	switch (phase)
	{
	case 0://title_appear
		t_alpha++;
		if (t_alpha >= 100)
			phase = 1;
		break;
	case 1://menu selection
		for (int i = 0; i < 4; i++)
		{
			if (i == selection)
			{
				m_alpha[i] = 255;
				m_size[i] = 1.f;
			}
			else
			{
				m_alpha[i] = 123;
				m_size[i] = 0.8f;
			}
		}

		//selecting
		if (INPUT_M->Pressed(VK_LEFT))
		{
			SOUND_M->Play("button_2", false)->SetVolume(-1000);
			selection--;
		}
		if (INPUT_M->Pressed(VK_RIGHT))
		{
			SOUND_M->Play("button_2", false)->SetVolume(-1000);
			selection++;
		}
		if (selection < 0) selection = 3;
		if (selection > 3) selection = 0;

		//selected
		if (INPUT_M->Pressed('Z'))
		{
			SOUND_M->Play("button_1", false)->SetVolume(-1000);
			switch (selection)
			{
			case 0:
				SCENE_M->Change("stage_1");
				break;
			case 1:
				phase = 2;
				break;
			case 2:
				phase = 3;
				break;
			case 3:
				exit(0);
				break;
			}
		}
		break;
	case 2://information
		if (INPUT_M->Pressed('Z'))
		{
			SOUND_M->Play("button_1", false)->SetVolume(-1000);
			phase = 1;
		}
		break;
	case 3://ranking
		if (INPUT_M->Pressed('Z'))
		{
			SOUND_M->Play("button_1", false)->SetVolume(-1000);
			phase = 1;
		}
		break;
	}

	//background
	if (_system->scroll_speed > 1.f) _system->scroll_speed -= 0.05f;
	if (_system->scroll_speed < 1.f) _system->scroll_speed += 0.05f;
	if (_system->background_red < 255) _system->background_red++;
	if (_system->background_black < 255) _system->background_black++;
}

void main_menu::Render()
{
	//title
	if (phase <= 1)
		RENDER_M->CenterRender(IMAGE_M->Find("m_title"), t_pos.x, t_pos.y, 0.1f, 1.f, 1.f, 0.f, D3DCOLOR_RGBA(255, 255, 255, (int)(255 * t_alpha / 100)));

	if (phase == 1)//menu
	{
		RENDER_M->CenterRender(IMAGE_M->Find("m_start"), 256, 560, 0.1f, m_size[0], m_size[0], 0.f, D3DCOLOR_RGBA(255, 255, 255, m_alpha[0]));
		RENDER_M->CenterRender(IMAGE_M->Find("m_info"), 512, 560, 0.1f, m_size[1], m_size[1], 0.f, D3DCOLOR_RGBA(255, 255, 255, m_alpha[1]));
		RENDER_M->CenterRender(IMAGE_M->Find("m_rank"), 768, 560, 0.1f, m_size[2], m_size[2], 0.f, D3DCOLOR_RGBA(255, 255, 255, m_alpha[2]));
		RENDER_M->CenterRender(IMAGE_M->Find("m_exit"), 1024, 560, 0.1f, m_size[3], m_size[3], 0.f, D3DCOLOR_RGBA(255, 255, 255, m_alpha[3]));
	}

	if (phase == 2)//information
	{
		RENDER_M->CenterRender(IMAGE_M->Find("m_detailed_info"), WINSIZEX / 2, WINSIZEY / 2, 0.2f);
		RENDER_M->CenterRenderText("Z키로 총알을 발사하여 공격할 수 있습니다", 740, 280, 0.1f, 40.f);
		RENDER_M->CenterRenderText("X키로 무기를 교체할 수 있습니다", 740, 360, 0.1f, 40.f);
		RENDER_M->CenterRenderText("3레벨 이후부터 A키로 보호막을 사용할 수 있습니다", 740, 440, 0.1f, 40.f);
		RENDER_M->CenterRenderText("5레벨 보호막으로 총알을 튕겨낼 수 있습니다", 740, 520, 0.1f, 40.f);
		RENDER_M->CenterRenderText("5레벨 이후부터 S키로 폭탄을 사용할 수 있습니다", 740, 600, 0.1f, 40.f);
	}

	if (phase == 3)//ranking
	{
		game_system* _system = static_cast<game_system*>(OBJECT_M->Find("game_system"));
		RENDER_M->CenterRender(IMAGE_M->Find("m_detailed_rank"), WINSIZEX / 2, WINSIZEY / 2, 0.1f);
		RENDER_M->RenderText("1st " + _system->ranked_name[0] + " " + to_string(_system->ranked_score[0]), 328, 220, 0.1f, 60.f);
		RENDER_M->RenderText("2nd " + _system->ranked_name[1] + " " + to_string(_system->ranked_score[1]), 328, 300, 0.1f, 60.f);
		RENDER_M->RenderText("3rd " + _system->ranked_name[2] + " " + to_string(_system->ranked_score[2]), 328, 380, 0.1f, 60.f);
		RENDER_M->RenderText("4th " + _system->ranked_name[3] + " " + to_string(_system->ranked_score[3]), 328, 460, 0.1f, 60.f);
		RENDER_M->RenderText("5th " + _system->ranked_name[4] + " " + to_string(_system->ranked_score[4]), 328, 540, 0.1f, 60.f);
	}
}

void main_menu::Release()
{
}