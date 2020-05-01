#include "SceneManager.h"
namespace core
{
	SceneManager::SceneManager(CGame* game,int ID_scene)
	{
		this->game = game;
		this->ID_scene = ID_scene;
	}
	SceneManager::~SceneManager()
	{
	}
	void SceneManager::Init(int id_scene)
	{
		ID_scene = id_scene;
		switch (id_scene)
		{
		case SCENE_1:
		
			LoadObjectsFromFile(L"Scenes\\Scene1_objects.txt");
			SetGameState(SCENE_1);
			break;
		}
	}
	void SceneManager::LoadResources()
	{
		simons = new simon::Simon();
		simons->LoadResources(textures, sprites, animations);
		
		ground = new static_object::Ground();
		ground->LoadResources(textures, sprites, animations);
		
		subweapon = new simon::SubWeapon();
		subweapon->LoadResources(textures, sprites, animations);
		
		whip = new simon::Whip();
		whip->LoadResources(textures, sprites, animations);
		
		candle = new static_object::Candle();
		candle->LoadResources(textures, sprites, animations);

		item = new static_object::Item();
		item->LoadResources(textures, sprites, animations);

		
		tilemaps->Add(SCENE_1, L"TileMap\\Scene_1_map.txt", L"Textures\\Scene_1_bank.png", 47 * 32, 11 * 32, 32, 32);
		textures->Add(ID_TEXTURE_BBOX, L"Textures\\bbox.png", D3DCOLOR_XRGB(0, 0, 0));
		
	}
	void SceneManager::LoadObjectsFromFile(LPCWSTR FilePath)
	{
		List_Objects_In_Game.clear();
		fstream fs;
		fs.open(FilePath, ios::in);
		if (fs.fail())
		{
			DebugOut(L"[ERROR]  Load data failed: file path = %s\n", FilePath);
			fs.close();
			return;
		}
		
		int ID_Obj;
		float pos_x, pos_y;
		int status;
		bool isEnable;
		int idItem;
		simons = new simon::Simon();
		List_Objects_In_Game.push_back(simons);
		subweapon = new simon::SubWeapon();
		subweapon->SetEnable(false);
		List_Objects_In_Game.push_back(subweapon);
		while (!fs.eof())
		{
			fs >> ID_Obj >> pos_x >> pos_y >> status >> isEnable >> idItem;
			switch (ID_Obj)
			{
			case GROUND:
				ground = new static_object::Ground();
				ground->SetPosition(pos_x, pos_y);
				ground->SetStatus(status);
				ground->SetEnable(isEnable);
				ground->Set_Id_item_that_obj_carry(idItem);
				List_Objects_In_Game.push_back(ground);
				break;
			case CANDLE:
				candle = new static_object::Candle();
				candle->SetPosition(pos_x, pos_y);
				candle->SetStatus(status);
				candle->SetEnable(isEnable);
				candle->Set_Id_item_that_obj_carry(idItem);
				List_Objects_In_Game.push_back(candle);
			default:
				break;
			}
		}
	}
	void SceneManager::Update(DWORD dt)
	{
		for(int i=0;i<List_Objects_In_Game.size();i++)
		{
			if (List_Objects_In_Game[i]->Is_Enable == false)
				continue;
			vector<LPGAMEOBJECT>co0bjects;
			if (dynamic_cast<simon::Simon*>(List_Objects_In_Game[i]))
			{
				for (int j = 0; j < List_Objects_In_Game.size(); j++)
				{
					if (List_Objects_In_Game[j]->Is_Enable == false)
						continue;
					co0bjects.push_back(List_Objects_In_Game[j]); //nạp tất cả object đang enable vào hàm update simon
				}
			}
			else if(dynamic_cast<static_object::Item*>(List_Objects_In_Game[i]))
			{
				for(int j=0;j<List_Objects_In_Game.size();j++)
				{
					if(List_Objects_In_Game[j]->Is_Enable == false)
						continue;
					if (dynamic_cast<static_object::Ground*>(List_Objects_In_Game[j]))
					{
						co0bjects.push_back(List_Objects_In_Game[j]);// thêm tất cả object là ground vào hàm update item
					}
				}
			}
			else if(dynamic_cast<simon::SubWeapon*>(List_Objects_In_Game[i]))
			{
				for (int j = 1; j < List_Objects_In_Game.size(); j++)
				{
					if (List_Objects_In_Game[j]->Is_Enable == false)
						continue;
					if (dynamic_cast<static_object::Ground*>(List_Objects_In_Game[j])) //Nạp tất cả object là Ground vào co0jects trong hàm update Subweapon de xu lý va chạm
					{
						co0bjects.push_back(List_Objects_In_Game[j]);
					}
					if (dynamic_cast<static_object::Candle*>(List_Objects_In_Game[j]))//Nạp tất cả object là candle vao co0jects trong hàm update Subweapon de xu ly va cham
					{
						co0bjects.push_back(List_Objects_In_Game[j]);
					}
				}
			}
			else
			{
				co0bjects.push_back(List_Objects_In_Game[i]);
			}
			List_Objects_In_Game[i]->Update(dt, &List_Objects_In_Game, &co0bjects);
		}
		//cập nhật vị trí CAM
		float sx, sy;
		simons->GetPosition(sx, sy);
		float cx, cy;
		game->GetCameraPositon(cx, cy);
		if (sx > SCREEN_WIDTH / 2 && sx + SCREEN_WIDTH / 2 < tilemaps->Get(ID_scene)->Get_Map_Width())
			game->SetCamaraPosition(sx - SCREEN_WIDTH / 2, 0);
		//va chạm cuối map. -70 là right của sprite simon
		if(sx>=tilemaps->Get(ID_scene)->Get_Map_Width()-70)
		{
			sx= tilemaps->Get(ID_scene)->Get_Map_Width()-70;
			simons->SetPosition(sx, sy);
		}
		//Subweapon ra khỏi camera thì sẽ biến mất
		float wx, wy;
		float cx1, cy1;
		subweapon->GetPosition(wx, wy);
		game->GetCameraPositon(cx1, cy1);
		if (wx > cx1 + SCREEN_WIDTH - 30 || wy > cy1 + SCREEN_WIDTH - 30 || wx < cx1 || wy < cy1)
		{
			subweapon->SetEnable(false);
		}
		//item ra khỏi camera thì sẽ biến mất
		for (int i = 0; i < List_Objects_In_Game.size(); i++)
		{
			if (dynamic_cast<static_object::Item*>(List_Objects_In_Game[i]))
			{
				game->GetCameraPositon(cx1, cy1);
				float ix, iy;
				List_Objects_In_Game[i]->GetPosition(ix, iy);
				if (ix > cx1 + SCREEN_WIDTH || iy > cy1 + SCREEN_WIDTH || ix < cx1 || iy < cy1)
				{
					List_Objects_In_Game[i]->SetEnable(false);
				}
			}
		}
	}
	void SceneManager::Render()
	{
		float cam_x, cam_y;
		game->GetCameraPositon(cam_x, cam_y);
		tilemaps->Get(ID_scene)->Draw(cam_x, cam_y);
		for (int i = 0; i < List_Objects_In_Game.size(); i++)
		{
			if (List_Objects_In_Game[i]->Is_Enable == false)
				continue;

			List_Objects_In_Game[i]->Render();
			List_Objects_In_Game[i]->RenderBBox();
		}
	}
	void SceneManager::SetGameState(int state)
	{
		switch (state)
		{
		case SCENE_1:
			simons->SetPosition(0.0f,0.0f);
			break;
		}
	}
}