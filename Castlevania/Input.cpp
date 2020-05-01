#include "Input.h"
namespace input
{
	Input::Input(core::CGame* game, core::SceneManager* scenes)
	{
		this->game = game;
		this->scenes = scenes;
	}
	Input::~Input()
	{
	}
	bool Input::Animation_Standby()
	{
		int status;
		scenes->Get_Simon()->GetStatus(status);
		if (status == UPDATE && scenes->Get_Simon()->animations[UPDATE]->IsOver(400)==false )
		{
			return true;
		}
		//3 frames
		if (status == ATTACK && scenes->Get_Simon()->animations[ATTACK]->IsOver(300) == false)
		{
			return true;
		}
		if (status == ATTACK_SIT && scenes->Get_Simon()->animations[ATTACK_SIT]->IsOver(300) == false)
		{
			return true;
		}
		if (status == ATTACK_STAND && scenes->Get_Simon()->animations[ATTACK_STAND]->IsOver(300) == false)
		{
			return true;
		}
		return false;
	}
	bool Input::CanProcessKeyboard()
	{
		if (Animation_Standby() == true)
		{
			return false;
		}
		int status;
		scenes->Get_Simon()->GetStatus(status);
		//Nếu simon k chạm đất và đang dứng ( đánh trên không trung) hoặc k chạm dất và đang nhảy thì không xử lý
		if ((scenes->Get_Simon()->isOntheGround == false && status == STAND) ||
			(scenes->Get_Simon()->isOntheGround == false && status == JUMP) || scenes->Get_Simon()->isFalling==true)
		{
			return false;
		}
		return true;
	}
	void Input::KeyState(BYTE* state)
	{
		if (CanProcessKeyboard() == false)
		{
			return;
		}
		if (game->IsKeyDown(DIK_RIGHT))
		{
			if (game->IsKeyDown(DIK_DOWN))
			{
				scenes->Get_Simon()->SetOrientation_x(1);
				scenes->Get_Simon()->SetStatus(SIT);
			}
			else
			{
				scenes->Get_Simon()->SetOrientation_x(1);
				scenes->Get_Simon()->SetStatus(WALK);
			}
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (game->IsKeyDown(DIK_DOWN))
			{
				scenes->Get_Simon()->SetOrientation_x(-1);
				scenes->Get_Simon()->SetStatus(SIT);
			}
			else
			{
				scenes->Get_Simon()->SetOrientation_x(-1);
				scenes->Get_Simon()->SetStatus(WALK);
			}
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			scenes->Get_Simon()->SetStatus(SIT);
		}
		else
		{
			scenes->Get_Simon()->SetStatus(STAND);
		}
	}

	void Input::OnKeyDown(int KeyCode)
	{
		if (KeyCode != DIK_Z)
		{
			if (CanProcessKeyboard() == false)
				return;
		}
		DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
		int status;
		scenes->Get_Simon()->GetStatus(status);
		switch (KeyCode)
		{
		case DIK_SPACE:
			scenes->Get_Simon()->SetStatus(JUMP);
			break;
		case DIK_Z:
			if (!game->IsKeyDown(DIK_UP))
			{
				if(status == JUMP || status == STAND)
				scenes->Get_Simon()->SetStatus(ATTACK_STAND);
				else if (status == SIT)
				{
					scenes->Get_Simon()->SetStatus(ATTACK_SIT);
				}
			}
			else if(game->IsKeyDown(DIK_UP))
			{
				bool enable;
				scenes->Get_Sub_Weapon()->GetEnable(enable);
				int status;
				scenes->Get_Simon()->GetStatus(status);
				if (scenes->Get_Simon()->GetSubweapon() == -1 || scenes->Get_Simon()->GetMana() == 0 || enable==true) // không có vũ khí hoặc enery = 0
					return;
				if (status == STAND || status == JUMP)
				{
					simon::Simon* simon = scenes->Get_Simon();
					simon::SubWeapon* weapon = scenes->Get_Sub_Weapon();
					float sx, sy;

					// position
					simon->GetPosition(sx, sy);
					weapon->SetPosition(sx, sy+10);
					int ox;
					simon->GetOrientation_x(ox);
					// orientation
					weapon->SetOrientation_x(ox);

					// state weapon
					weapon->SetState(simon->GetSubweapon());

					weapon->SetEnable(true);
					int mana;
					mana= simon->GetMana();
					simon->SetMana(mana-1);
					simon->SetStatus(ATTACK);
				}
			}
			break;
		case DIK_1:
			scenes->Get_Simon()->SetSubweapon(DAGGER);
			break;
		case DIK_2:
			scenes->Get_Simon()->SetSubweapon(FLYING_AXE);
			break;
		case DIK_3:
			scenes->Get_Simon()->SetSubweapon(BOOMERANG);
			break;
		case DIK_4:
			scenes->Get_Simon()->SetSubweapon(HOLY_WATER);
			break;
		case DIK_Q:
			scenes->Init(SCENE_1);
			break;
		}
	}
	void Input::OnKeyUp(int KeyCode)
	{
		DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	}
}