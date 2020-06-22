#pragma once

#include "d3dx9.h"
#include "Utils.h"
#include "Texture.h"
#include "Sprite.h"
#include "Simon.h"
#include "SceneManager.h"

#include <vector>
#include <string>

using namespace  std;
namespace HUD
{
	class HUD
	{
	private:
		core::SceneManager* scenes;
		core::CGame* game;
		simon::Simon* simons;

		ID3DXFont* font;
		string information;

		vector<core::LPSPRITE>playerHp;
		vector<core::LPSPRITE>enemyHP;
		vector<core::LPSPRITE>loseHP;

		int Score;
		int Time;
		int Scene;
		int Subweapon;
		int Mana;
		int life;
		int HP;
		int item;
		int bossHP;

	public:
		HUD(core::SceneManager* scenes, core::CGame* game);
		~HUD();

		void Init();
		void Update(DWORD dt);
		void Render();
	};
}

