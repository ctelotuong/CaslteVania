#include "HUD.h"
namespace HUD
{
	HUD::HUD(core::SceneManager* scenes, core::CGame* game)
	{
		this->scenes = scenes;
		this->game = game;
		this->simons = scenes->Get_Simon();

		Time = 0;
	}
	 HUD::~HUD()
	 {
		 
	 }

	void HUD::Init()
	{
		D3DCOLOR transparentColor = D3DCOLOR_XRGB(116, 116, 116);
		core::CTexture* texture = core::CTexture::GetInstance();
		texture->Add(ID_TEXTURES_HP, L"Textures\\HP.png", transparentColor);
		texture->Add(ID_)
	}

}