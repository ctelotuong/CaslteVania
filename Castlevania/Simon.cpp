﻿#include "Simon.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
namespace simon
{
	Simon::Simon() : CGameObject()
	{
		SetStatus(STAND);

		Add_Animation_into_state(STAND_ANIMATION);
		Add_Animation_into_state(WALK_ANIMATION);
		Add_Animation_into_state(SIT_ANIMATION);
		Add_Animation_into_state(JUMP_ANIMATION);
		Add_Animation_into_state(HIT_SIT_ANIMATION);
		Add_Animation_into_state(HIT_STAND_ANIMATION);
		Add_Animation_into_state(HIT_STAND_ANIMATION);
		Add_Animation_into_state(UPDATE_ANIMATION);

		whip = new Whip();
		Mana = 14;
		Life = 3;
		Subweapon = -1;
		HP = 10;
	}
	void Simon::Update(DWORD dt, vector<core::LPGAMEOBJECT>* List_Objects_In_Game, vector<core::LPGAMEOBJECT>* coObjects)
	{
		core::CGameObject::Update(dt);
		//Cho tốc độ simon nhảy lên nhanh gấp 2 lần khi simon rơi xuống
		if (vy >= 0 && vy <= SIMON_SPEED_JUMP/2)
		{
			vy += HALF_OF_GRAVITY * dt;
		}
		else
		{
			vy += GRAVITY * dt;
			isFalling = true;
			//tránh lun giữ trạng thái ATTACK_STAND khi simon rơi xuống làm quay lại FRAME đầu.
			if(vy > 0.6f)
			{
				status = STAND;
			}
		}
		//Xét va chạm với item
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			core::LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<static_object::Item*>(obj))
			{
				static_object::Item* e = dynamic_cast<static_object::Item*>(obj);
				float left, top, right, bottom;
				e->GetBBox(left, top, right, bottom);
				if (CheckCollisionSimonAndItem(left, top, right, bottom) == true)
				{
					obj->SetEnable(false);
					int idItem;
					obj->GetStatus(idItem);
					switch (idItem)
					{
					case STOP_WATCH:
					case DAGGER:
					case FLYING_AXE:
					case HOLY_WATER:
					case BOOMERANG:
						Subweapon = idItem;
						break;
					case SMALL_HEART:
						Mana += 1;
						break;
					case LAGRE_HEART:
						Mana += 5;
						break;
					case CHAIN:
						SetStatus(UPDATE);
						vx = 0;
						// lên đời whip
						int status;
						whip->GetStatus(status);
						if (status == NORMAL_WHIP) whip->SetStatus(SHORT_WHIP);
						else if (status == SHORT_WHIP) whip->SetStatus(MORNING_STAR_WHIP);
						break;
					default:
						break;
					}
				}
			}
		}
		
		//Va chạm với cạnh màn hình
		if (x < 0)
			x = 0;
		//Xét va chạm với vật thể
		vector<core::LPCOLLISIONEVENT> coEvents;
		vector<core::LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			//Khi va chạm thì sẽ đẩy ra 1 chút
			x += min_tx * dx + nx * 0.1f;
			y += min_ty * dy + ny * 0.1f;
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				core::LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<static_object::Candle*>(e->obj))
				{
					//cho phép đi qua lun candle
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;
				}
				else if (dynamic_cast<static_object::Ground*>(e->obj))
				{
					if (ny < 0)
					{
						vy = 0;
						isOntheGround = true;
						isFalling = false;
					}
				}
				else if(dynamic_cast<static_object::Item*>(e->obj))
				{
					if (e->nx != 0) x += dx;
					if (e->ny != 0) y += dy;
				}
			}
		}
		// clean up collision events
		for (int i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
		if (status == ATTACK_SIT || status == ATTACK_STAND)
		{
			// lấy vị trí của simon để set vị trí cho roi
			whip->SetOrientation_x(Orientation_x);
			whip->SetWhipPosition(x, y, isStand);
			if (animations[status]->GetCurrentFrame() == animations[status]->GetFramesSize() - 1) // chỉ xét va chạm khi render tới sprite cuối cùng của roi
			{
				for (UINT i = 0; i < coObjects->size(); i++)
				{
					core::LPGAMEOBJECT obj = coObjects->at(i);
					if (dynamic_cast<static_object::Candle*>(obj))
					{
						static_object::Candle* e = dynamic_cast<static_object::Candle*> (obj);
						float left, top, right, bottom;
						e->GetBBox(left, top, right, bottom);
						if (whip->CheckCollisionWhipAndStuff(left, top, right, bottom) == true) // va chạm giữa roi và nến dùng AABB
						{
							e->SetStatus(CANDLE_DESTROY);
						}
					}
				}
			}
		}
		
	}
	void Simon::Render()
	{
		
		animations[status]->Render(1, Orientation_x, x, y);
		if(status==ATTACK_SIT || status==ATTACK_STAND)
		{
			whip->Render(animations[status]->GetCurrentFrame());
		}
	}
	void Simon::SetStatus(int status)
	{
		core::CGameObject::SetStatus(status);
		switch (status)
		{
		case STAND:
			isStand = true;
			isOntheGround = true;
			vx = 0;
			break;
		case WALK:
			if (Orientation_x > 0)
				vx = SIMON_WALK_SPEED;
			else
				vx = -SIMON_WALK_SPEED;
			break;
		case JUMP:
			isOntheGround = false;
			vy = -SIMON_SPEED_JUMP;
			break;
		case SIT:
			vx = 0;
			isStand = false;
			isOntheGround = true;
			break;
		case ATTACK_SIT:
			isStand = false;
			isOntheGround = true;
			animations[status]->Reset();
			animations[status]->SetAniStartTime(GetTickCount());
			break;
		case ATTACK_STAND:
		case ATTACK:
		case UPDATE:
			isStand = true;
			animations[status]->Reset();
			animations[status]->SetAniStartTime(GetTickCount());
			break;
		default:
			break;
		}
	}
	void Simon::GetBBox(float& B_left, float& B_top, float& B_right, float& B_bottom)
	{
		//sprite của SIMON là 70x70, BBox là 40x64
		B_left = x + 13;
		B_top = y + 8;
		B_right = B_left + 40;
		B_bottom = B_top + 64;

	}
	void Simon::LoadResources(core::CTexture*& textures, core::CSprites*& sprites, core::CAnimations*& animations)
	{
		D3DCOLOR transparentColor = D3DCOLOR_XRGB(116, 116, 116);
		textures->Add(ID_TEXTURE_SIMON, L"Textures\\Simon.png", transparentColor);
		LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEXTURE_SIMON);
		ifstream sprite_reader;
		sprite_reader.open(L"Sprite\\Simon.txt");
		if (sprite_reader.fail())
		{
			DebugOut(L"[ERROR]");
		}
		int spriteid;
		int top, left, right, bottom;
		while (sprite_reader >> spriteid >> left >> top >> right >> bottom)
		{
			sprites->Add(spriteid, left, top, right, bottom, texSimon);
		}
		sprite_reader.close();

		ifstream animation_reader;
		animation_reader.open(L"Animation\\Simon.txt");
		if (!animation_reader)
		{
			DebugOut(L"[ERROR]");
		}
		int animation_id;
		string line;
		int sprite_id;
		int frameTime;
		while (getline(animation_reader, line))
		{
			core::LPANIMATION ani = new core::CAnimation();
			istringstream iss(line, istringstream::in);
			iss >> animation_id;
			while (iss >> sprite_id >> frameTime)
				ani->Add(sprite_id, frameTime);
			animations->Add(animation_id, ani);
		}
		animation_reader.close();
	}
	bool Simon::CheckCollisionSimonAndItem(float left, float top, float right, float bottom)
	{
		float simon_left, simon_top, simon_right, simon_bottom;
		GetBBox(simon_left, simon_top, simon_right, simon_bottom);
		return AABB(simon_left, simon_top, simon_right, simon_bottom, left, top, right, bottom);
	}

}