#pragma once

#include <Windows.h>

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include <d3dx9.h>
#include <d3d9.h>

using namespace std;

void DebugOut(const wchar_t* fmt, ...);

vector<string> split(string line, string delimeter = "\t");
wstring ToWSTR(string st);

LPCWSTR ToLPCWSTR(string st);
#pragma region Main.cpp

#define MAIN_WINDOW_NAME	L"Casltevania"
#define MAIN_WINDOW_TITLE	L"Casltecania-Early Acess(broken game) but you still need to pay money to play it (Game industry parody)"

#define BACKGROUND_BACKBUFFER	D3DCOLOR_XRGB(0,0,255)
#define SCREEN_WIDTH			640
#define SCREEN_HEIGHT			480

#define MAX_FRAME_RATE			120
#pragma endregion

#pragma region Game

#define KEYBOARD_BUFFER_SIZE	1024
#define DIRECTINPUT_VERSION 0x0800

#pragma endregion
#pragma region ID scene
#define SCENE_1	0
#define SCENE_2	1
#define SCENE_2_2	2
#define SCENE_3	3
#define SCENE_3_3	4
#define SCENE_4	5
#pragma endregion
#pragma region ID Texture
#define ID_TEXTURE_BBOX		0
#define ID_TEXTURE_SIMON	1
#define ID_TEXTURE_GROUND	2
#define ID_TEXTURE_CANDLE	3
#define ID_TEXTURE_WHIP		4
#define ID_TEXTURE_TILEMAP_SCENE_1	5
#define ID_TEXTURE_TILEMAP_SCENE_2	6
#define ID_TEXTURE_TILEMAP_SCENE_2_2	7
#define ID_TEXTURE_TILEMAP_SCENE_3	8
#define ID_TEXTURE_TILEMAP_SCENE_3_2	9
#define ID_TEXTURE_TILEMAP_SCENE_4	10

#define ID_TEXTURES_ITEM_STOP_WATCH 11
#define ID_TEXTURES_ITEM_DAGGER		12
#define ID_TEXTURES_ITEM_FLYING_AXE		13
#define ID_TEXTURES_ITEM_HOLY_WATER		14
#define ID_TEXTURES_ITEM_BOOMERANG		15
#define ID_TEXTURES_ITEM_SMALL_HEART		16
#define ID_TEXTURES_ITEM_LARGE_HEART		17
#define ID_TEXTURES_ITEM_CHAIN			18

#define ID_TEXTURES_WEAPONS_AXE			19
#define ID_TEXTURES_WEAPONS_HOLY_WATER	20
#define ID_TEXTURES_WEAPONS_BOOMERANG	21
#define ID_TEXTURES_WEAPONS_DAGGER		22
#pragma endregion

#pragma region ID ANIMATION SIMON
#define STAND_ANIMATION	101
#define WALK_ANIMATION	102
#define SIT_ANIMATION	103
#define JUMP_ANIMATION	104
#define HIT_SIT_ANIMATION	105
#define HIT_STAND_ANIMATION	106
#define UPDATE_ANIMATION		107
#pragma endregion

#pragma region ID ANIMATION WHIPS
#define NORMAL_WHIP_ANIMATION	201
#define SHORT_WHIP_ANIMATION	202
#define MORNING_STAR_WHIP_ANIMATION		203
#pragma endregion

#pragma region ID ANI GROUND
#define GROUND_ANIMATION_1		401
#define GROUND_ANIMATION_2		402
#define GROUND_ANIMATION_2_2	403
#define GROUND_ANIMATION_3		404
#define GROUND_ANIMATION_3_2	405
#define GROUND_ANIMATION_4		406
#pragma endregion

#pragma region ID ANI CANDLE
#define BIG_CANDLE_ANIMATION	501
#define SMALL_CANDLE_ANIMATION	502
#pragma endregion

#pragma region  ID ANI ITEMS
#define STOP_WATCH_ANIMATION	601
#define Dagger_ANIMATION		602
#define FLYING_AXE_ANIMATION	603
//What Is this, a special crossover :v between castlevanina and DOOM (also MeMe from bojack hourse man)
//It is just :v holy_water
//hope you enjoy this little easter egg
#define DOOM_SLAYER_FAVORITE_WATER_TO_RIP_AND_TEAR_ALL_THE_DEMON 604
#define BOOMMERANG_ANIMATION	605
#define SMALL_HEART_ANIMATION				606
#define LARGE_HEART_ANIMATION				607
#define CHAIN_ANIMATION					608
#pragma  endregion

#pragma region ID ANI WEAPON
#define WEAPONS_STOP_WATCH_ANIMATION	701
#define WEAPONS_DAGGER_ANIMATION		702
#define WEAPONS_AXE_ANIMATION			703
#define WEAPONS_HOLY_WATER_ANIMATION	704
#define WEAPONS_BOOMERANG_ANIMATION		705
#define USING_HOLY_WATER_ANIMATION		706
#pragma endregion

#pragma region STATE SIMON
#define STAND	0
#define WALK	1
#define SIT		2
#define JUMP	3
#define ATTACK_SIT	4
#define ATTACK_STAND	5
#define ATTACK		6
#define	UPDATE	7
#pragma endregion

#pragma region STATE WHIP
#define NORMAL_WHIP	0
#define SHORT_WHIP	1
#define MORNING_STAR_WHIP 2
#pragma endregion

#pragma region STATE GROUND
#define GROUND_1	0
#define GROUND_2	1
#define GROUND_2_2	2
#define GROUND_3	3
#define GROUND_3_2	4
#define GROUND_4	5
#pragma endregion

#pragma region STATE CANDLE
#define BIG_CANDLE	0
#define SMALL_CANDLE	1
#define CANDLE_DESTROY	2
#pragma endregion

#pragma region STATE ITEM
#define STOP_WATCH 0
#define DAGGER		1
#define FLYING_AXE	2
#define HOLY_WATER	3
#define BOOMERANG	4
#define USING_HOLY_WATER	5
#define SMALL_HEART	5
#define LAGRE_HEART	6
#define CHAIN	7

#pragma endregion 
#pragma region ALL PARAMETER FOR UPDATE SIMON
#define SIMON_SPEED_JUMP	0.5f
#define SIMON_WALK_SPEED	0.1f
#define GRAVITY				0.002f
#define HALF_OF_GRAVITY		0.001f

#pragma region ALL PAREMTER FOR UPDATE SUBWEAPON
#define WEAPONS_DAGGER_SPEED		0.3f

#define WEAPONS_AXE_SPEED_X			0.2f
#define WEAPONS_AXE_SPEED_Y			0.5f

#define WEAPONS_HOLY_WATER_SPEED_X	0.23f
#define WEAPONS_HOLY_WATER_SPEED_Y	0.1f

#define WEAPONS_BOOMERANG_SPEED		0.5f
#pragma endregion

#define GROUND		0
#define CANDLE		1