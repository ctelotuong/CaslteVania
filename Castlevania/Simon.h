#pragma once
#include <vector>

#include "GameObject.h"
#include "Utils.h"
#include "Candle.h"
#include "Ground.h"
#include "Whip.h"
#include "SubWeapon.h"
namespace simon
{
	class Simon:public core::CGameObject
	{
		Whip* whip;
		
		int Score;
		int Mana;
		int Life;
		int Subweapon;
		int HP;
	public:
		bool isStand = true;
		bool isOntheGround = false;
		bool isFalling = false;
		bool isOnStair = false;
		bool IsJumping = false;
		
		Simon();

		virtual void GetBBox(float& B_left, float& B_top, float& B_right, float& B_bottom);
		virtual void Update(DWORD dt, vector<core::LPGAMEOBJECT>* List_Objects_In_Game = NULL, vector<core::LPGAMEOBJECT>* coObjects = NULL);
		void Render();
		void SetStatus(int status);
		virtual void LoadResources(core::CTexture*& textures, core::CSprites*& sprites, core::CAnimations*& animations);
		//////////////////
		///////GET////////
		//////////////////
		int GetScore() { return this->Score; }
		int GetMana() { return this->Mana; }
		int	GetLife() { return this->Life; }
		int GetHP() { return this->HP; }
		int GetSubweapon() { return this->Subweapon; }
		bool Get_Is_Stand() { return this->isStand; }
		bool Get_Isontheground() { return this->isOntheGround; }
		bool Get_Is_Falling() { return this->isFalling; }
		bool Get_Is_Onstair() { return this->isOnStair; }
		bool Get_Is_Jumping() { return this->IsJumping; }
		///////////////////
		///////SET/////////
		///////////////////
		void SetScore(int score) { this->Score = score; }
		void SetMana(int mana) { this->Mana = mana; }
		void SetLife(int life) { this->Life = life;}
		void SetHP(int hp) { this->HP = hp; }
		void SetSubweapon(int id_subweapon) { this->Subweapon = id_subweapon; }
		void Set_Is_Stand(bool true_false) { this->isStand=true_false; }
		void Set_Isontheground(bool true_false) { this->isOntheGround= true_false; }
		void Set_Is_Falling(bool true_false) {this->isFalling= true_false; }
		void Set_Is_Onstair(bool true_false) { this->isOnStair= true_false; }
		void Set_Is_Jumping(bool true_false) { this->IsJumping= true_false; }
		/////////////////////////////////////////////////////
		/////CHECK COLLISION SIMON WITH OTHER STUFF//////////
		/////////////////////////////////////////////////////
		bool CheckCollisionSimonAndItem(float top, float left, float right, float bottom);
		bool CheckCollisionSimonAndStair(float top, float left, float right, float bottom);
	};
}

