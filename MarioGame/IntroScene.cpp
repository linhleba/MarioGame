
#include <iostream>
#include <fstream>

#include "IntroScene.h"
#include "Utils.h"
#include "Textures.h"
#include "ScrollBackground.h"
#include "BrickIntro.h"
#include "BackgroundIntro.h"
#include "Number.h"
#include "Item.h"
#include "Star.h"

using namespace std;

CIntroScene::CIntroScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CIntroSceneKeyHandler(this);
	CGame::GetInstance()->SetCamPos(0, -20);
}


void CIntroScene::_ParseSection_TEXTURES(string line)
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

void CIntroScene::_ParseSection_SPRITES(string line)
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

void CIntroScene::_ParseSection_ANIMATIONS(string line)
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

void CIntroScene::_ParseSection_ANIMATION_SETS(string line)
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

void CIntroScene::_ParseSection_OBJECTS(string line)
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

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO_RED: obj = new CMario(OBJECT_TYPE_MARIO_RED, x, y);
		redMario = (CMario*)obj;
		break;
	case OBJECT_TYPE_BRICK: obj = new CBrickIntro(); break;
	case OBJECT_TYPE_SCROLLING_BACKGROUND: obj = new CScrollBackground(); break;
	case OBJECT_TYPE_MARIO_GREEN: obj = new CMario(OBJECT_TYPE_MARIO_GREEN, x, y);
		greenMario = (CMario*)obj;
		break;
	case OBJECT_TYPE_FIRST_BACKGROUND: obj = new CBackgroundIntro(OBJECT_TYPE_FIRST_BACKGROUND);
		firstBackground.push_back((CBackgroundIntro*)obj);
		break;
	case OBJECT_TYPE_SECOND_BACKGROUND: obj = new CBackgroundIntro(OBJECT_TYPE_SECOND_BACKGROUND);
		secondBackground = (CBackgroundIntro*)obj;
		break;
	case OBJECT_TYPE_FINAL_BACKGROUND: obj = new CBackgroundIntro(OBJECT_TYPE_FINAL_BACKGROUND);
		finalBackground = (CBackgroundIntro*)obj;
		break;
	case OBJECT_TYPE_NUMBER_THREE: obj = new CNumber();
		number = (CNumber*)obj;
		break;

	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(OBJECT_TYPE_GOOMBA);
		goomba = (CGoomba*)obj;
		break;
	case OBJECT_TYPE_ITEM: obj = new CItem();
		item.push_back((CItem*)obj);
		break;
	case OBJECT_TYPE_STAR: obj = new CStar();
		star = (CStar*)obj;
		break;
	case OBJECT_TYPE_KOOPAS_GREEN_NORMAL: obj = new CKoopas(OBJECT_TYPE_KOOPAS_GREEN_NORMAL);
		greenKoopas = (CKoopas*)obj;
		break;
	case OBJECT_TYPE_KOOPAS_BLACK: obj = new CKoopas(OBJECT_TYPE_KOOPAS_BLACK);
		blackKoopas = (CKoopas*)obj;
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

void CIntroScene::Load()
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



void CIntroScene::Render()
{
	for (size_t i = 0; i < objects.size(); i++)
		objects[i]->Render();
}


/*
	Unload current scene
*/
void CIntroScene::Update(DWORD dt)
{
	if (!isTimeStart)
	{
		// set disappeared before count time
		greenMario->SetIsAppeared(false);
		redMario->SetIsAppeared(false);
		time_start = GetTickCount();
		goomba->SetState(GOOMBA_STATE_DISAPPEAR);
		greenKoopas->SetState(KOOPAS_STATE_DISAPPEAR);
		blackKoopas->SetState(KOOPAS_STATE_DISAPPEAR);
		isTimeStart = true;
	}
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	/*double cx, cy;
	greenMario->GetPosition(cx, cy);
	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	CGame::GetInstance()->SetCamPos(round(cx), -20.0f);*/

	if (!firstTime_start)
	{
		if (GetTickCount() - time_start > TIME_MARIO_APPEARED)
		{
			greenMario->SetIsAppeared(true);
			if (greenMario->GetIsAbleGreenWalk())
			{
				greenMario->SetState(MARIO_STATE_WALKING_RIGHT);
			}
			redMario->SetIsAppeared(true);
			if (greenMario->GetIsAbleRedWalk())
			{
				redMario->SetState(MARIO_STATE_WALKING_LEFT);
			}
			redMario->nx = -1;
			firstTime_start = true;
		}
	}

	if (greenMario->x >= 320 && greenMario->GetIsHolding() == false)
	{
		greenMario->nx = -1;
		greenMario->SetState(MARIO_STATE_IDLE);
		greenMario->SetIsAbleGreenWalk(false);
	}

	if (!secondTime_start)
	{
		if (GetTickCount() - time_start > TIME_MARIO_GREEN_JUMP)
		{
			if (countJumpGreen == 0)
			{
				greenMario->SetState(MARIO_STATE_JUMP);
				countJumpGreen++;
			}
			secondTime_start = true;
		}
	}

	if (redMario->GetState() == MARIO_STATE_SITDOWN)
	{
		if (!isTimeRedSitDown)
		{
			timeRedSitDown_start = GetTickCount();
			isTimeRedSitDown = true;
		}
		else
		{
			if (GetTickCount() - timeRedSitDown_start > 600)
			{
				redMario->SetState(MARIO_STATE_IDLE);
				isRedStandUp = true;
			}
		}
	}

	// func when red mario stand up, MARIO BROS 3 will appear
	if (isRedStandUp == true)
	{
		secondBackground->SetState(BACKGROUND_STATE_APPEAR);
		isRedStandUp = false;
		//number->SetState(NUMBER_THREE_STATE_APPEAR);
		//finalBackground->SetState(BACKGROUND_STATE_APPEAR);
	}

	// second background is end up
	if (secondBackground->GetIsEndingSecondBackground())
	{
		if (!isSetFinalBackground)
		{
			for (size_t i = 0; i < firstBackground.size(); i++)
			{
				firstBackground.at(i)->SetState(BACKGROUND_STATE_DISAPPEAR);
			}
			finalBackground->SetState(BACKGROUND_STATE_APPEAR);
			goomba->SetState(GOOMBA_STATE_FALL);
			greenKoopas->SetState(KOOPAS_STATE_DIE);
			blackKoopas->SetState(KOOPAS_STATE_DIE);
			star->SetState(STAR_STATE_APPEAR);
			number->SetState(NUMBER_THREE_STATE_APPEAR);
			for (size_t i = 0; i < item.size(); i++)
			{
				int checkPos = item.at(i)->CheckPositionItemIntro();
				if (checkPos == 1)
				{
					item.at(i)->SetState(ITEM_STATE_MUSHROOM_APPEAR);
					item.at(i)->SetSpeed(-item.at(i)->vx, item.at(i)->vy);
				}
				else if (checkPos == 2)
				{
					item.at(i)->SetState(ITEM_STATE_LEAF_APPEAR);
				}

			}
			isSetFinalBackground = true;
		}
	}
	// check when koopas fall on the head of Red Mario
	if (redMario->GetState() == MARIO_STATE_BEING_HITTED)
	{
		if (!isTimeHitted)
		{
			timeHitted_start = GetTickCount();
			isTimeHitted = true;
		}
		else
		{
			if (GetTickCount() - timeHitted_start > 350)
			{
				redMario->SetState(MARIO_STATE_LOOKING_AHEAD);
				timeLookAhead_start = GetTickCount();
			}
		}
	}

	// check when look ahead ani
	if (redMario->GetState() == MARIO_STATE_LOOKING_AHEAD)
	{
		if (GetTickCount() - timeLookAhead_start > 1100)
		{
			redMario->SetState(MARIO_STATE_JUMP);
			redMario->SetIsJumping(true);
		}
	}

	if (redMario->GetLevel() == MARIO_LEVEL_TAIL && !checkFirstTimeTail)
	{
		if (!firstTimeGoombaWalking)
		{
			goomba->SetState(GOOMBA_STATE_WALKING);
			firstTimeGoombaWalking = true;
		}
		if (goomba->GetState() == GOOMBA_STATE_WALKING)
		{
			if (!redMario->GetCheckFall())
			{
				if (GetTickCount() - checkFall_start > 40)
				{
					redMario->SetState(MARIO_STATE_FALL_IDLE);
					redMario->SetCheckFall(true);
					checkFall_start = GetTickCount();
				}
			}
			else
			{
				if (GetTickCount() - checkFall_start > 40)
				{
					redMario->SetCheckFall(false);
					checkFall_start = GetTickCount();
				}
			}
		}
		else
		{
			// check idle if Goomba doesn't die
			if (!firstGoombadie)
			{
				redMario->SetState(MARIO_STATE_IDLE);
				redMario->nx = 1;
				redMario->SetCheckFall(false);
				firstGoombadie = true;
			}
		}

		// if state Idle, give the amounnt of time to set state walking right, declear firstTimeToShoot to check condition
		if (redMario->GetState() == MARIO_STATE_IDLE)
		{
			if (!firstTimeToShoot)
			{
				if (!checkIdleStart)
				{
					checkIdle_start = GetTickCount();
					checkIdleStart = true;
				}

				else
				{
					if (GetTickCount() - checkIdle_start > 600)
					{
						redMario->SetState(MARIO_STATE_WALKING_RIGHT);
						checkWalkingStart = true;
						firstTimeToShoot = true;
						checkWalking_start = GetTickCount();
					}
				}
			}
		}
		// check walking time to set the idle mario status
		if (firstTimeToShoot)
		{
			if (GetTickCount() - checkWalking_start > 1900)
			{
				redMario->SetState(MARIO_STATE_IDLE);
				//checkWalkingStart = false;
				checkFirstTimeTail = true;
			}
		}
	}

	if (greenKoopas->GetState() == KOOPAS_STATE_RUNNING_SHELL_RIGHT)
	{
		if (countTimeRunning == 0)
		{
			firstTimeRunning_start = GetTickCount();
			countTimeRunning++;
		}
		else if (countTimeRunning == 1)
		{
			if (GetTickCount() - firstTimeRunning_start > 1500)
			{
				greenKoopas->SetState(KOOPAS_STATE_DIE);
				//greenKoopas->SetPosition(greenKoopas->x, greenKoopas->y - 0.2f);
				countTimeRunning++;
			}
		}

		if (countTimeRunning == 4)
		{
			if (GetTickCount() - firstTimeToRedRunning_start > 500)
			{
				redMario->SetState(MARIO_STATE_JUMP);
			}
			countTimeRunning++;
		}
		if (countTimeRunning == 5)
		{
			redMario->SetState(MARIO_STATE_IDLE);
		}
	}

	if (greenKoopas->GetState() == KOOPAS_STATE_DIE)
	{
		if (countTimeRunning == 2)
		{
			countTimeRunning++;
			firstTimeGreenHold_start = GetTickCount();
			greenMario->SetState(MARIO_STATE_WALKING_LEFT);
			greenMario->SetIsHolding(true);
		}
		if (countTimeRunning == 3)
		{
			//DebugOut(L"hdello there");
			if (GetTickCount() - firstTimeGreenHold_start > 800)
			{
				greenMario->SetIsHolding(false);
				greenMario->SetState(MARIO_STATE_IDLE);
				redMario->SetState(MARIO_STATE_WALKING_LEFT);
				firstTimeToRedRunning_start = GetTickCount();
				countTimeRunning++;
			}
		}
	}
}

void CIntroScene::Unload()
{
	for (size_t i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CIntroSceneKeyHandler::OnKeyUp(int KeyCode)
{
	/*CMario* mario = ((CIntroScene*)scence)->GetPlayer();
	double pX, pY;
	mario->GetPosition(pX, pY);
	switch (KeyCode)
	{
	}*/
}

void CIntroSceneKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario* mario = ((CIntroScene*)scence)->GetPlayer();
	//double pX, pY;
	//mario->GetPosition(pX, pY);
	switch (KeyCode)
	{
	case DIK_W:
		CGame::GetInstance()->SwitchScene(INDEX_OF_PLAY_SCENE);
		break;
	}
}

void CIntroSceneKeyHandler::KeyState(BYTE* states)
{
	/*CGame* game = CGame::GetInstance();
	CMario* mario = ((CIntroScene*)scence)->GetPlayer();*/
}





