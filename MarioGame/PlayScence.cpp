#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "define.h"
#include "BackgroundObject.h"
#include "Question.h"
#include "Pipe.h"
#include "ColorBrick.h"
#include "Coin.h"
#include "FireBall.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	DebugOut(L"--> %s\n", ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_KOOPAS: obj = new CKoopas(); break;
	case OBJECT_TYPE_BOBJECT: obj = new CBackgroundObject(); break;
	case OBJECT_TYPE_QUESTION: obj = new CQuestion(); break;
	case OBJECT_TYPE_PIPE:	obj = new CPipe(); break;
	case OBJECT_TYPE_COLORBRICK: obj = new CColorBrick(); break;
	case OBJECT_TYPE_COIN:	obj = new CCoin(); break;
	case OBJECT_TYPE_FIREBALL:	obj = new CFireBall(); break;
	case OBJECT_TYPE_PORTAL:
	{
		DebugOut(L"Portal");
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	if (cx < 0) cx = 0;
	else if (cx > 2816) cx = 2816;
	if (player->GetLevel() != MARIO_LEVEL_TAIL)
	{
		CGame::GetInstance()->SetCamPos(round(cx), -35.0f);
	}
	else
	{
		if (cy > -40)
		{
			CGame::GetInstance()->SetCamPos(round(cx), -35.0f);
		}
		else
		{
			CGame::GetInstance()->SetCamPos(round(cx), round(cy));
		}
	}
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	float pX, pY;
	mario->GetPosition(pX, pY);
	switch (KeyCode)
	{
	case DIK_A:
		mario->SetIsHolding(true);
		break;
	case DIK_S:
		if (!mario->IsJumping())
		{
			if (!mario->CheckHighSpeedStart())
			{
				mario->SetState(MARIO_STATE_JUMP);
			}
			else
			{
				mario->SetState(MARIO_STATE_JUMP_HIGH_SPEED);
			}
			mario->SetIsJumping(true);
		}
		break;
	case DIK_P:
		mario->Reset();
		break;
	case DIK_Q:
		DebugOut(L"Press key down Q \n");
		if (mario->GetLevel() != MARIO_LEVEL_SMALL)
		{
			mario->SetPosition(pX, pY - 1.0f);
		}
		else
		{
			mario->SetPosition(pX, pY - 20.0f);
		}
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_W:
		DebugOut(L"Press key down W \n");
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_E:
		DebugOut(L"Press key down E \n");
		if (mario->GetLevel() != MARIO_LEVEL_SMALL)
		{
			mario->SetPosition(pX, pY - 1.5f);
		}
		else
		{
			mario->SetPosition(pX, pY - 20.0f);
		}
		mario->SetLevel(MARIO_LEVEL_FIRE);
		break;
	case DIK_R:
		DebugOut(L"Press key down R");
		if (mario->GetLevel() != MARIO_LEVEL_SMALL)
		{
			mario->SetPosition(pX, pY - 2.0f);
		}
		else
		{
			mario->SetPosition(pX, pY - 20.0f);
		}
		mario->SetLevel(MARIO_LEVEL_TAIL);
		break;
	// flying tail mario
	case DIK_D:
		if (mario->GetLevel() == MARIO_LEVEL_TAIL)
		{
			if (mario->IsStartFlying() == false)
			{
				mario->SetStartFlying();
			}
			if (mario->CheckTimeForFalling())
			{
				mario->SetState(MARIO_STATE_FLYING_IDLE);
			}
			else
			{
				mario->SetCheckFall(true);
				mario->SetState(MARIO_STATE_FALL_IDLE);
			}
		}
		break;
	case DIK_Z:
		if (mario->GetLevel() == MARIO_LEVEL_FIRE)
		{
			mario->SetShootFire(true);
		}
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	float pX, pY;
	mario->GetPosition(pX, pY);
	switch (KeyCode)
	{
	case DIK_A:
		// Set is running
		mario->SetIsRunning(false);
		mario->SetTurnBackTail(false);
		mario->SetBoostSpeed(0);
		mario->SetIsHolding(false);
		// Set high speed to false
		mario->SetHighSpeed(false);
		mario->SetIsFirstTimeHighSpeed(false);
		break;
	case DIK_RIGHT:
		if (!mario->CheckStateFlying() )
		{
			mario->SetState(MARIO_STATE_IDLE);
		}
		break;
	case DIK_LEFT:
		if (!mario->CheckStateFlying())
		{
			mario->SetState(MARIO_STATE_IDLE);
		}
		break;
	case DIK_D: 
		mario->SetCheckFall(false);

	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;
	// boost speed for mario
	if (game->IsKeyDown(DIK_A))
	{
		// Declare to set ani mario for running
		mario->SetIsRunning(true);

		// turn back if tail mario after holding A 
		if (mario->GetLevel() == MARIO_LEVEL_TAIL && !mario->HasTurnBackTail())
		{
			mario->StartTurningBack();
			mario->SetState(MARIO_STATE_TURN);
		}
		if (game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_RIGHT))
		{
			if (mario->GetState() != MARIO_STATE_HIGH_SPEED_LEFT && mario->GetState() != MARIO_STATE_HIGH_SPEED_RIGHT)
			{

				mario->SetBoostSpeed(0.05);
			}
			else 
			{
				mario->SetBoostSpeed(0.12);
			}
		}
		if (game->IsKeyDown(DIK_RIGHT))
		{
			//DebugOut(L"key down right]n");
			if (!mario->CheckStateFlying())
			{
				// if the first time or mario is idle, we will reset counttime
				if (!mario->GetIsFirstTimeHighSpeed() || mario->GetState() == MARIO_STATE_IDLE)
				{
					mario->SetIsFirstTimeHighSpeed(true);
					// Set the time to run high-speed
					mario->StartHighSpeed();
				}
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
			}
			else
			{
				mario->SetState(MARIO_STATE_FLYING_RIGHT);
			}
		}
		else if (game->IsKeyDown(DIK_LEFT)) {
			//DebugOut(L" keydown left \n");
			if (!mario->CheckStateFlying())
			{
				// if the first time or mario is idle, we will reset counttime
				if (!mario->GetIsFirstTimeHighSpeed() || mario->GetState() == MARIO_STATE_IDLE)
				{
					// Set the time to run high-speed
					mario->SetIsFirstTimeHighSpeed(true);
					mario->StartHighSpeed();
				}
				mario->SetState(MARIO_STATE_WALKING_LEFT);
			}
			else
			{
				mario->SetState(MARIO_STATE_FLYING_LEFT);
			}
		}
		else
			if (!mario->CheckStateFlying())
			{
				mario->SetState(MARIO_STATE_IDLE);
			}
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		if (!mario->CheckStateFlying())
		{	
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else
		{
			if (mario->CheckTimeForFalling())
			{
				mario->SetState(MARIO_STATE_FLYING_RIGHT);
			}
			else
			{
				mario->SetState(MARIO_STATE_FALL_RIGHT);
			}
		}
	}

	else if (game->IsKeyDown(DIK_LEFT))
		if (!mario->CheckStateFlying())
		{
			mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else 
		{
			if (mario->CheckTimeForFalling())
			{
				mario->SetState(MARIO_STATE_FLYING_LEFT);
			}
			else
			{
				mario->SetState(MARIO_STATE_FALL_LEFT);
			}
		}
	else
		if (!mario->CheckStateFlying())
		{
			mario->SetState(MARIO_STATE_IDLE);		
		}

}