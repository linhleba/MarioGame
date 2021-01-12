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
#include "Item.h"
#include "Flower.h"
#include "FireFlower.h"
#include "BreakableBrick.h"
#include "PLetter.h"
#include "CoinQuestion.h"
#include "HUD.h"
#include "Card.h"
#include "Score.h"
#include "Tail.h"
#include "Fragments.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	numPos.assign(3, 0);
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
	for (size_t i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
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

	for (size_t i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->emplace_back(ani);
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
	double x = atof(tokens[1].c_str());
	double y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;
	CHUD* timeCounter = NULL;
	CHUD* scoreCounter = NULL;
	CHUD* moneyCounter = NULL;
	CHUD* stackNormalCounter = NULL;
	CHUD* stackMax = NULL;
	CHUD* staticItem = NULL;
	CHUD* cardCounter = NULL;
	CHUD* life = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO_RED:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;
		player->SetLevel(CGame::GetInstance()->GetLevel());

		DebugOut(L"[INFO] Player object created!\n");
		break;
	//case OBJECT_TYPE_BOBJECT: obj = new CBackgroundObject(); break;
	//case OBJECT_TYPE_GOOMBA: obj = new CGoomba(OBJECT_TYPE_GOOMBA); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	//case OBJECT_TYPE_KOOPAS_GREEN_NORMAL: obj = new CKoopas(OBJECT_TYPE_KOOPAS_GREEN_NORMAL); break;
	//case OBJECT_TYPE_QUESTION: obj = new CQuestion(); break;
	//case OBJECT_TYPE_PIPE:	obj = new CPipe(); break;
	//case OBJECT_TYPE_COLORBRICK: obj = new CColorBrick(); break;
	//case OBJECT_TYPE_COIN:	obj = new CCoin(); break;
	case OBJECT_TYPE_FIREBALL:	obj = new CFireBall(); break;
	//case OBJECT_TYPE_ITEM:	obj = new CItem(); break;
	//case OBJECT_TYPE_FLOWER: obj = new CFlower(); break;
	//case OBJECT_TYPE_FIREFLOWER: obj = new CFireFlower(); break;
	//case OBJECT_TYPE_BREAKABLEBRICK: obj = new CBreakableBrick(); break;
	//case OBJECT_TYPE_PLETTER: obj = new CPLetter(); break;
	//case OBJECT_TYPE_COINQUESTION: obj = new CCoinQuestion(); break;
	//case OBJECT_TYPE_KOOPAS_GREEN_FLYING: obj = new CKoopas(OBJECT_TYPE_KOOPAS_GREEN_FLYING); break;
	//case OBJECT_TYPE_KOOPAS_RED_NORMAL: obj = new CKoopas(OBJECT_TYPE_KOOPAS_RED_NORMAL); break;
	//case OBJECT_TYPE_GOOMBA_FLYING:	obj = new CGoomba(OBJECT_TYPE_GOOMBA_FLYING); break;
	case OBJECT_TYPE_HUD_PANEL:
		staticItem = new CHUD(OBJECT_TYPE_HUD_PANEL);
		break;
	case OBJECT_TYPE_HUD_WORLD:
		staticItem = new CHUD(OBJECT_TYPE_HUD_WORLD);
		break;
	case OBJECT_TYPE_HUD_MARIO_LUIGI:
		staticItem = new CHUD(OBJECT_TYPE_HUD_MARIO_LUIGI);
		break;
	case OBJECT_TYPE_HUD_LIFE:
		life = new CHUD(OBJECT_TYPE_HUD_LIFE);
		break; 
	case OBJECT_TYPE_HUD_TIME_PICKER:
		timeCounter = new CHUD(OBJECT_TYPE_HUD_TIME_PICKER);
		break;
	case OBJECT_TYPE_HUD_SCORE:
		//timeCounter = new CHUD(OBJECT_TYPE_HUD_SCORE);
		scoreCounter = new CHUD(OBJECT_TYPE_HUD_SCORE);
		break;
	case OBJECT_TYPE_HUD_MONEY:
		moneyCounter = new CHUD(OBJECT_TYPE_HUD_MONEY);
		break;
	case OBJECT_TYPE_HUD_STACK_NORMAL:
		stackNormalCounter = new CHUD(OBJECT_TYPE_HUD_STACK_NORMAL);
		break;
	case OBJECT_TYPE_HUD_STACK_MAX:
		stackMax = new CHUD(OBJECT_TYPE_HUD_STACK_MAX);
		break;
	case OBJECT_TYPE_HUD_BLACK:
		staticItem = new CHUD(OBJECT_TYPE_HUD_BLACK);
		break;
	case OBJECT_TYPE_HUD_CARD:
		cardCounter = new CHUD(OBJECT_TYPE_HUD_CARD);
		break;
	/*case OBJECT_TYPE_FINAL_CARD:
		obj = new CCard();
		break;*/
	case OBJECT_TYPE_SCORE:
		obj = new CScore();
		score = (CScore*)obj;
		break;
	case OBJECT_TYPE_TAIL:
		obj = new CTail();
		break;
	/*case OBJECT_TYPE_PIPE_DOWNING:
		obj = new CPipe(OBJECT_TYPE_PIPE_DOWNING);
		break;
	case OBJECT_TYPE_PIPE_UPPING:
		obj = new CPipe(OBJECT_TYPE_PIPE_UPPING);
		break;
	case OBJECT_TYPE_GREEN_MUSHROOM:
		obj = new CItem(OBJECT_TYPE_GREEN_MUSHROOM);
		break;
	case OBJECT_TYPE_SPECIAL_BRICK:
		obj = new CQuestion(OBJECT_TYPE_SPECIAL_BRICK);
		break;*/
	/*case OBJECT_TYPE_FIRST_WORD:
		obj = new CBackgroundObject(OBJECT_TYPE_FIRST_WORD);
		break;
	case OBJECT_TYPE_SECOND_WORD:
		obj = new CBackgroundObject(OBJECT_TYPE_SECOND_WORD);
		break;
	case OBJECT_TYPE_THIRD_WORD_ITEM:
		obj = new CBackgroundObject(OBJECT_TYPE_THIRD_WORD_ITEM);
		break;*/
	case OBJECT_TYPE_FRAGMENT_LEFTTOP:
		obj = new CFragments(OBJECT_TYPE_FRAGMENT_LEFTTOP);
		break;
	case OBJECT_TYPE_FRAGMENT_RIGHTTOP:
		obj = new CFragments(OBJECT_TYPE_FRAGMENT_RIGHTTOP);
		break;
	case OBJECT_TYPE_FRAGMENT_LEFTBOTTOM:
		obj = new CFragments(OBJECT_TYPE_FRAGMENT_LEFTBOTTOM);
		break;
	case OBJECT_TYPE_FRAGMENT_RIGHTBOTTOM:
		obj = new CFragments(OBJECT_TYPE_FRAGMENT_RIGHTBOTTOM);
		break;
	case OBJECT_TYPE_PORTAL:
	{
		DebugOut(L"Portal");
		double r = atof(tokens[4].c_str());
		double b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	// General object setup
	if (obj != NULL)
	{
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		objects.emplace_back(obj);
	}
	if (timeCounter != NULL)
	{
		timeCounter->SetPosition(x, y);
		timeCounter->SetAnimationSet(ani_set);
		timeCounters.emplace_back(timeCounter);
	}
	if (scoreCounter != NULL)
	{
		scoreCounter->SetPosition(x, y);
		scoreCounter->SetAnimationSet(ani_set);
		scoreCounters.emplace_back(scoreCounter);
	}

	if (moneyCounter != NULL)
	{
		moneyCounter->SetPosition(x, y);
		moneyCounter->SetAnimationSet(ani_set);
		moneyCounters.emplace_back(moneyCounter);
	}
	
	if (stackNormalCounter != NULL)
	{
		stackNormalCounter->SetPosition(x, y);
		stackNormalCounter->SetAnimationSet(ani_set);
		stackNormalCounters.emplace_back(stackNormalCounter);
	}

	if (stackMax != NULL)
	{
		stackMax->SetPosition(x, y);
		stackMax->SetAnimationSet(ani_set);
		stackMaxCounter = (CHUD*)stackMax;
	}
	
	if (staticItem != NULL)
	{
		staticItem->SetPosition(x, y);
		staticItem->SetAnimationSet(ani_set);
		staticItems.emplace_back(staticItem);
	}
	if (cardCounter != NULL)
	{
		cardCounter->SetPosition(x, y);
		cardCounter->SetAnimationSet(ani_set);
		cardCounters.emplace_back(cardCounter);
	}
	if (life != NULL)
	{
		life->SetPosition(x, y);
		life->SetAnimationSet(ani_set);
		lifeCounter = (CHUD*)life;
	}
}

void CPlayScene::_ParseSection_GRID(string line)
{
	//LPGRID grid = new Grid();
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());
	LPCWSTR path = ToLPCWSTR(tokens[0]);
	grid = new Grid(path);

}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 7) return; // skip invalid lines

	int idTileSet = atoi(tokens[0].c_str());
	int totalRowsTileSet = atoi(tokens[1].c_str());
	int totalColumnsTileSet = atoi(tokens[2].c_str());
	int totalRowsMap = atoi(tokens[3].c_str());
	int totalColumnsMap = atoi(tokens[4].c_str());
	int totalTiles = atoi(tokens[5].c_str());
	wstring file_path = ToWSTR(tokens[6]);

	map = new Map(idTileSet, totalRowsTileSet, totalColumnsTileSet, totalRowsMap, totalColumnsMap, totalTiles);
	map->LoadMap(file_path.c_str());
	map->ExtractTileFromTileSet();
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
		if (line == "[GRID]")
		{
			section = SCENE_SECTION_GRID; continue;
		}
		if (line == "[MAP]")
		{
			section = SCENE_SECTION_MAP; continue;
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
		case SCENE_SECTION_GRID: _ParseSection_GRID(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	numPos.at(VECTOR_INDEX_HUNDREDS_POSITION) = (int)(timeStart / 100);
	numPos.at(VECTOR_INDEX_TENS_POSITION) = (timeStart / 10) % 10;
	numPos.at(VECTOR_INDEX_UNITS_POSITION) = (timeStart) % 10;

	// Update time start
	if (!isResetTimeStart)
	{
		resetTime_start = GetTickCount();
		isResetTimeStart = true;
	}
	else
	{
		if (GetTickCount() - resetTime_start >= 1000)
		{
			isResetTimeStart = false;
			timeStart--;
		}
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	double cx, cy;
	player->GetPosition(cx, cy);
	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	//DebugOut(L"cx la %f \n", cx);


	// Before setting the current position, save the info into the previous Cam
	if (id == INDEX_OF_MAP_1_SCENE || id == INDEX_OF_MAP_4_SCENE)
	{
		camPreX = game->GetCamX();
		camPreY = game->GetCamY();
	}
	if (cx <= 0) cx = 0;
	//if (cx > 2816) cx = 2816;
	if (cx >= 2500) cx = 2500;

	//DebugOut(L" cx la %f \n", cx);
	if (id == INDEX_OF_BASE_SCENE)
	{
		CGame::GetInstance()->SetCamPos(1300, 990);
	}

	if (id == INDEX_OF_MAP_1_SCENE)
	{
		if (player->GetLevel() != MARIO_LEVEL_TAIL)
		{
			if (cy > -150)
			{
				CGame::GetInstance()->SetCamPos(round(cx), round(-50.0f));
			}
			else
			{
				CGame::GetInstance()->SetCamPos(round(cx), round(cy));
			}
		}
		else
		{
			if (cy > -40)
			{
				CGame::GetInstance()->SetCamPos(round(cx), -50.0f);
			}
			else
			{
				CGame::GetInstance()->SetCamPos(round(cx), round(cy));
			}
		}
		
	}

	if (id == INDEX_OF_MAP_4_SCENE)
	{
		CGame::GetInstance()->SetCamPos(round(cx), 220.0f);
	}

	player->GetPosition(cx, cy);

	
	for (size_t i = 0; i < coObjects.size(); i++)
	{
		double x = coObjects[i]->x;
		double y = coObjects[i]->y;
		if (!CheckInViewPortCam(x, y))
		{
			coObjects[i]->SetIsActive(false);
			coObjects.erase(coObjects.begin() + i);
		}
	}

	// Update grid and handle to pass the current cells into the currentObjects
	if (grid != NULL)
	{
		grid->HandleGrid(&coObjects, game->GetCamX(), game->GetCamY(), game->GetScreenWidth(), game->GetScreenHeight());
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetIsActive() == false)
		{
			coObjects.emplace_back(objects[i]);
			objects[i]->SetIsActive(true);
		}
	}
	//objects.clear();



	/*if (!player->GetIsTransforming())
	{
		for (size_t i = 0; i < coObjects.size(); i++)
		{
			coObjects[i]->Update(dt, &coObjects);
		}
	}
	else
	{
		for (size_t i = 0; i < coObjects.size(); i++)
		{
			if (dynamic_cast<CMario*>(coObjects[i]))
			{
				coObjects[i]->Update(dt, &coObjects);
			}
		}
	}*/


	for (size_t i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->Update(dt, &coObjects);
	}

	// Update items object
	for (size_t i = 0; i < staticItems.size(); i++)
	{
		staticItems[i]->Update(dt, &coObjects);
	}

	for (size_t i = 0; i < timeCounters.size(); i++)
	{
		timeCounters[i]->Update(dt, &coObjects);
	}
	for (size_t i = 0; i < scoreCounters.size(); i++)
	{
		scoreCounters[i]->Update(dt, &coObjects);
	}
	for (size_t i = 0; i < moneyCounters.size(); i++)
	{
		moneyCounters[i]->Update(dt, &coObjects);
	}
	for (size_t i = 0; i < stackNormalCounters.size(); i++)
	{
		stackNormalCounters[i]->Update(dt, &coObjects);
	}
	if (stackMaxCounter != NULL)
	{
		stackMaxCounter->Update(dt, &coObjects);
	}
	for (size_t i = 0; i < cardCounters.size(); i++)
	{
		cardCounters[i]->Update(dt, &coObjects);
	}
	if (lifeCounter != NULL)
	{
		lifeCounter->Update(dt, &coObjects);
	}

}

void CPlayScene::Render()
{
	double cx, cy;
	player->GetPosition(cx, cy);
	CGame* game = CGame::GetInstance();

	if (map)
	{
		this->map->Render();
	}

	for (size_t i = 0; i < coObjects.size(); i++)
	{
		coObjects.at(i)->Render();
	}

	for (size_t i = 0; i < staticItems.size(); i++)
	{
		staticItems[i]->Render();
	}

	for (size_t i = 0; i < timeCounters.size(); i++)
	{
		timeCounters[i]->Render(numPos.at(i));
	}
	for (size_t i = 0; i < scoreCounters.size(); i++)
	{
		scoreCounters[i]->Render(i);
	}
	for (size_t i = 0; i < moneyCounters.size(); i++)
	{
		moneyCounters[i]->Render(i);
	}
	for (size_t i = 0; i < stackNormalCounters.size(); i++)
	{
		stackNormalCounters[i]->Render(i);
	}
	stackMaxCounter->Render(0);

	for (size_t i = 0; i < cardCounters.size(); i++)
	{
		cardCounters[i]->Render(i);
	}
	lifeCounter->Render(0);

}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	// update level of Mario before unloading
	CGame::GetInstance()->SetLevel(player->GetLevel());

	for (size_t i = 0; i < objects.size(); i++)
		delete objects[i];

	for (size_t i = 0; i < staticItems.size(); i++)
	{
		delete staticItems[i];
	}

	for (size_t i = 0; i < timeCounters.size(); i++)
	{
		delete timeCounters[i];
	}
	for (size_t i = 0; i < scoreCounters.size(); i++)
	{
		delete scoreCounters[i];
	}
	for (size_t i = 0; i < moneyCounters.size(); i++)
	{
		delete moneyCounters[i];
	}
	for (size_t i = 0; i < stackNormalCounters.size(); i++)
	{
		delete stackNormalCounters[i];
	}
	//delete stackMaxCounter;

	for (size_t i = 0; i < cardCounters.size(); i++)
	{
		delete cardCounters[i];
	}

	//grid->GetObjectsInGrid().clear();
	coObjects.clear();
	objects.clear();
	staticItems.clear();
	timeCounters.clear();
	scoreCounters.clear();
	moneyCounters.clear();
	stackNormalCounters.clear();
	cardCounters.clear();
	player = NULL;
	delete map;
	map = nullptr;


	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}


void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	double pX, pY;
	mario->GetPosition(pX, pY);
	if (mario->GetLockControl()) return;
	switch (KeyCode)
	{
	case DIK_A:
		mario->SetIsHolding(true);
		if (mario->GetLevel() == MARIO_LEVEL_FIRE && mario->GetState() != MARIO_STATE_SITDOWN)
		{
			mario->SetShootFire(true);
			mario->SetAniShootFire(true);
		}
		if (mario->GetLevel() == MARIO_LEVEL_TAIL)
		{
			//mario->StartTurningBack();
			mario->SetFirstTailing(true);
		}
		break;
	case DIK_S:
		if (mario->CheckHighSpeedStart())
		{
			mario->SetIsAbleToFly(true);
		}
		if (mario->GetLevel() == MARIO_LEVEL_TAIL && mario->GetIsAbleToFly())
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
		else if (!mario->IsJumping())
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
		else if(mario->IsJumping() && mario->GetLevel() == MARIO_LEVEL_TAIL)
		{
			mario->SetCheckFall(true);
			mario->SetState(MARIO_STATE_FALL_IDLE);
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

	case DIK_Z:
		/*if (mario->GetLevel() == MARIO_LEVEL_FIRE && mario->GetState() != MARIO_STATE_SITDOWN)
		{
			mario->SetShootFire(true);
			mario->SetAniShootFire(true);
		}*/
		break;
	case DIK_0:
		CGame::GetInstance()->SwitchScene(INDEX_OF_WORLD_MAP_SCENE);
		CGame::GetInstance()->SetCamPos(0, -50);
		break;
	case DIK_1:
		mario->SetPosition(0, 0);
		break;
	case DIK_2:
		mario->SetPosition(560, 102);
		break;
	case DIK_3:
		mario->SetPosition(1330, 80);
		break;
	case DIK_4:
		mario->SetPosition(2000, 0);
		break;
	case DIK_5:
		mario->SetPosition(2255, -200);
		break;
	case DIK_6:
		mario->SetPosition(2476, 102);
		break;
	case DIK_7:
		mario->SetPosition(1328, -150);
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	double pX, pY;
	mario->GetPosition(pX, pY);
	if (mario->GetLockControl()) return;
	switch (KeyCode)
	{
	case DIK_A:
		// Set is running
		mario->SetIsRunning(false);
		//mario->SetTurnBackTail(false);
		mario->SetBoostSpeed(0);
		mario->SetIsHolding(false);
		// Set high speed to false
		mario->SetHighSpeed(false);
		mario->SetIsFirstTimeHighSpeed(false);
		// Set false to fire mario
		mario->SetShootFire(false);
		mario->SetAniShootFire(false);
		break;
	case DIK_RIGHT:
		if (!mario->CheckStateFlyingAndFall() )
		{
			mario->SetState(MARIO_STATE_IDLE);
		}
		break;
	case DIK_LEFT:
		if (!mario->CheckStateFlyingAndFall())
		{
			mario->SetState(MARIO_STATE_IDLE);
		}
		break;
	case DIK_S: 
		mario->SetCheckFall(false);
		break;
	case DIK_Z:
		/*mario->SetShootFire(false);
		mario->SetAniShootFire(false);*/
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Mario die 
	if (mario->GetLockControl()) return;
	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (game->IsKeyDown(DIK_A))
	{
		if (mario->GetState() == MARIO_STATE_IDLE && !mario->CheckStateFlying())
		{
			mario->SetTheStackDown();
		}
		// Declare to set ani mario for running
		if (!mario->GetFlagHolding())
		{
			mario->SetIsRunning(true);
		}
		if (game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_RIGHT))
		{
			if (!mario->GetFlagHolding())
			{
				if (mario->GetState() != MARIO_STATE_HIGH_SPEED_LEFT && mario->GetState() != MARIO_STATE_HIGH_SPEED_RIGHT)
				{

					mario->SetBoostSpeed(0.05f);
				}
				else
				{
					mario->SetBoostSpeed(0.12f);
				}
			}
		}
		if (game->IsKeyDown(DIK_RIGHT))
		{
			if (!mario->CheckStateFlying())
			{
				if (!mario->GetFlagHolding())
				{
					// if the first time or mario is idle, we will reset counttime
					if (!mario->GetIsFirstTimeHighSpeed() || mario->GetState() == MARIO_STATE_IDLE)
					{
						mario->SetIsFirstTimeHighSpeed(true);
						// Set the time to run high-speed
						mario->StartHighSpeed();
					}
				}
				else
				{
					mario->SetIsFirstTimeHighSpeed(false);
					mario->SetHighSpeed(false);
				}
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
			}
			else
			{
				//mario->SetIsFirstTimeHighSpeed(true);
				if (mario->CheckTimeForFalling())
				{
					mario->SetState(MARIO_STATE_FLYING_RIGHT);
					mario->SetTheStackUp();
				}
				else
				{
					mario->SetState(MARIO_STATE_FALL_RIGHT);
				}
			}

			if (!game->IsKeyDown(DIK_A) && !mario->CheckStateFlying())
			{
				mario->SetTheStackDown();
			}
		}
		else if (game->IsKeyDown(DIK_LEFT)) {
			if (!mario->CheckStateFlying())
			{
				if (!mario->GetFlagHolding())
				{
					// if the first time or mario is idle, we will reset counttime
					if (!mario->GetIsFirstTimeHighSpeed() || mario->GetState() == MARIO_STATE_IDLE)
					{
						// Set the time to run high-speed
						mario->SetIsFirstTimeHighSpeed(true);
						mario->StartHighSpeed();
					}
				}
				else
				{
					mario->SetIsFirstTimeHighSpeed(false);
					mario->SetHighSpeed(false);
				}
				mario->SetState(MARIO_STATE_WALKING_LEFT);
			}
			else
			{
				//mario->SetIsFirstTimeHighSpeed(true);
				if (mario->CheckTimeForFalling())
				{
					mario->SetState(MARIO_STATE_FLYING_LEFT);
					mario->SetTheStackUp();
				}
				else
				{
					mario->SetState(MARIO_STATE_FALL_LEFT);
				}
			}
			if (!game->IsKeyDown(DIK_A) && !mario->CheckStateFlying())
			{
				mario->SetTheStackDown();
			}
		}
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		if (!mario->IsStartFlying())
		{
			if (mario->GetCheckFall())
			{
				mario->SetState(MARIO_STATE_FALL_RIGHT);
			}
			else
			{
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
			}
		}
		else
		{
			if (mario->CheckTimeForFalling())
			{
				mario->SetState(MARIO_STATE_FLYING_RIGHT);
				mario->SetTheStackUp();
			}
			else
			{
				mario->SetState(MARIO_STATE_FALL_RIGHT);
			}
		}
	}

	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (!mario->IsStartFlying())
		{
			if (mario->GetCheckFall())
			{
				mario->SetState(MARIO_STATE_FALL_LEFT);
			}
			else
			{
				mario->SetState(MARIO_STATE_WALKING_LEFT);
			}
		}
		else
		{
			if (mario->CheckTimeForFalling())
			{
				mario->SetState(MARIO_STATE_FLYING_LEFT);
				mario->SetTheStackUp();
			}
			else
			{
				mario->SetState(MARIO_STATE_FALL_LEFT);
			}
		}
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{ 
		mario->SetState(MARIO_STATE_SITDOWN);
		if (mario->GetIsDowningPipe())
		{
			mario->SetState(MARIO_STATE_PIPE_STANDING);
			return;
		}
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		if (mario->GetIsUppingPipe())
		{
			mario->SetState(MARIO_STATE_PIPE_STANDING);
			return;
		}
	}
	else
	{
		if (!mario->CheckStateFlyingAndFall() && mario->GetState() != MARIO_STATE_PIPE_STANDING)
		{
			mario->SetState(MARIO_STATE_IDLE);
		}
	}
	if (!game->IsKeyDown(DIK_A) && !mario->CheckStateFlying())
	{
		mario->SetTheStackDown();
	}


}