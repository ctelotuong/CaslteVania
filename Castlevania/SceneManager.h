#pragma once
#include "Game.h"
#include "Ground.h"
#include "Candle.h"
#include "Utils.h"
#include "Texture.h"
#include "Sprite.h"
#include "Texture.h"

#include <string>
#include <fstream>
#include <sstream>
#include "Simon.h"
#include "Whip.h"
#include "TileMap.h"
#include "Item.h"
#include "SubWeapon.h"
namespace core
{
	class SceneManager
	{
		CGame* game;
		static_object::Ground* ground;
		static_object::Candle* candle;
		static_object::Item* item;
		simon::Simon* simons;
		simon::Whip* whip;
		simon::SubWeapon* subweapon;
		TileMaps* tilemaps = TileMaps::GetInstance();
		CTexture* textures = CTexture::GetInstance();
		CSprites* sprites = CSprites::GetInstance();
		CAnimations* animations = CAnimations::GetInstance();


		vector<LPGAMEOBJECT>List_Objects_In_Game;
		int ID_scene;
	public:
		SceneManager(CGame* game, int ID_scene);
		~SceneManager();

		void LoadResources();
		void LoadObjectsFromFile(LPCWSTR FilePath);
		virtual void Update(DWORD dt);
		virtual void Render();
		void Init(int id_scene);
		void SetGameState(int state);

		simon::Simon* Get_Simon() { return this->simons; }
		simon::SubWeapon* Get_Sub_Weapon() { return this->subweapon; };
	};
}
