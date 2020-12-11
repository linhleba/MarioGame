#include <iostream>
#include <fstream>

#include "WorldMapScene.h"
#include "Utils.h"
#include "Scence.h"
#include "Map.h"
#include "ObjectWorldMap.h"
#include "PlayerWorldMap.h"
#include "HUD.h"

#define SCENE_SECTION_MAP				7
using namespace std;

CWorldMap::CWorldMap(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CWorldMapScenceKeyHandler(this);
}


void CWorldMap::_ParseSection_TEXTURES(string line)
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

void CWorldMap::_ParseSection_SPRITES(string line)
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

void CWorldMap::_ParseSection_ANIMATIONS(string line)
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
void CWorldMap::_ParseSection_MAP(string line)
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

void CWorldMap::_ParseSection_ANIMATION_SETS(string line)
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
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void CWorldMap::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	double x = atof(tokens[1].c_str());
	double y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	int id;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		obj = new CPlayerWorldMap();
		mario = (CPlayerWorldMap*)obj;
		break;
	case OBJECT_TYPE_HELP:
		obj = new CObjectWorldMap(OBJECT_TYPE_HELP);
		break;
	case OBJECT_TYPE_GOLD_DIGGER:
		obj = new CObjectWorldMap(OBJECT_TYPE_GOLD_DIGGER);
		break;
	case OBJECT_TYPE_BUSH:
		obj = new CObjectWorldMap(OBJECT_TYPE_BUSH);
		break;
	case OBJECT_TYPE_NODE:
		id = atof(tokens[4].c_str());
		obj = new CNode(id);
		nodeList->AddNode((CNode*)obj);
		break;
	case OBJECT_TYPE_HUD_PANEL:
		obj = new CHUD(OBJECT_TYPE_HUD_PANEL);
		break;
	case OBJECT_TYPE_HUD_WORLD:
		obj = new CHUD(OBJECT_TYPE_HUD_WORLD);
		break;
	case OBJECT_TYPE_HUD_MARIO_LUIGI:
		obj = new CHUD(OBJECT_TYPE_HUD_MARIO_LUIGI);
		break;
	/*case OBJECT_TYPE_HUD_LIFE:
		obj = new CHUD(OBJECT_TYPE_HUD_LIFE);
		break; */
	case OBJECT_TYPE_HUD_TIME_PICKER:
		obj = new CHUD(OBJECT_TYPE_HUD_TIME_PICKER);
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

void CWorldMap::Load()
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
		if (line == "[MAP]") { section = SCENE_SECTION_MAP; continue; }
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
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}
	nodeList->SetTheDirection();
	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CWorldMap::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}


	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	nodeList->Update(dt, &coObjects);

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	CGame::GetInstance()->SetCamPos(0, 0);
}



void CWorldMap::Render()
{
	if (map)
	{
		this->map->Render();
	}

	for (size_t i = 0; i < objects.size(); i++)
		objects[i]->Render();
}


/*
	Unload current scene
*/
void CWorldMap::Unload()
{
	for (size_t i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	delete map;
	map = nullptr;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CWorldMapScenceKeyHandler::OnKeyUp(int KeyCode)
{

}

void CWorldMapScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CPlayerWorldMap* mario = ((CWorldMap*)scence)->GetPlayer();
	CWorldMap *worldmap = ((CWorldMap*)scence);
	CNodeList* nodeList = ((CWorldMap*)scence)->GetNodeList();
	if (mario->GetState() == MARIO_STATE_NOT_MOVING && !worldmap->GetIsKeyDown())
	{
		switch (KeyCode)
		{
		case DIK_DOWN:
			if (mario->GetIsNotMoving())
			{
				if (nodeList->FindTheDirection(VECTOR_INDEX_BOTTOM_DIRECTION))
				{
					worldmap->SetIsKeyDown(true);
					mario->SetState(MARIO_STATE_MOVING_DOWN);
				}
			}
			break;
		case DIK_UP:
			if (mario->GetIsNotMoving())
			{
				if (nodeList->FindTheDirection(VECTOR_INDEX_TOP_DIRECTION))
				{
					worldmap->SetIsKeyDown(true);
					mario->SetState(MARIO_STATE_MOVING_UP);
				}
			}
			break;
		case DIK_LEFT:
			if (mario->GetIsNotMoving())
			{
				if (nodeList->FindTheDirection(VECTOR_INDEX_LEFT_DIRECTION))
				{
					worldmap->SetIsKeyDown(true);
					mario->SetState(MARIO_STATE_MOVING_LEFT);
				}
			}
			break;
		case DIK_RIGHT:
			if (mario->GetIsNotMoving())
			{
				if (nodeList->FindTheDirection(VECTOR_INDEX_RIGHT_DIRECTION))
				{
					worldmap->SetIsKeyDown(true);
					mario->SetState(MARIO_STATE_MOVING_RIGHT);
				}
			}
			break;
		case DIK_W: 
			CGame::GetInstance()->SwitchScene(INDEX_OF_PLAY_SCENE);
			break;
		default:
			break;
		}
	}
}

void CWorldMapScenceKeyHandler::KeyState(BYTE* states)
{

}





