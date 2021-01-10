#include "Grid.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include "Goomba.h"
#include "Brick.h"
#include "Koopas.h"
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
#include "PlayScence.h"
#include "BackgroundObject.h"

Grid::Grid()
{
}

Grid::Grid(LPCWSTR path)
{
	ifstream f;
	f.open(path);

	// current resource section flag
	int section = GRID_SECTION_UNKNOWN;

	char str[MAX_GRID_LINE];
	while (f.getline(str, MAX_GRID_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") { section = GRID_SECTION_SETTINGS; continue; }
		if (line == "[OBJECTS]") {
			section = GRID_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }
		switch (section)
		{
		case GRID_SECTION_SETTINGS: 
			_ParseSection_SETTINGS(line);
			break;
		case GRID_SECTION_OBJECTS:
			_PareseSection_OBJECTS(line);
			break;

		}
	}

	f.close();

	//CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	DebugOut(L"[INFO] Done loading scene resources %s\n", path);
}

void Grid::HandleGrid()
{
	listGameObjectGrid.clear();
	CMario* mario = ((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer();
	int indexRow = mario->x / sizeOfCell;
	int indexColumn = (mario->y + 400) / sizeOfCell;

	DebugOut(L"index row is %d \n", indexRow);
	DebugOut(L"index column is %d \n", indexColumn);

	if (indexRow < 1)
	{
		indexRow = 1;
	}
	if (indexColumn < 1)
	{
		indexColumn = 1;
	}
	if (indexColumn > numOfColumns)
	{
		indexColumn = indexColumn - 1;
	}
	if (indexRow > numOfRows)
	{
		indexRow = indexRow - 1;
	}
	/*listGameObjectGrid.push_back(cells[indexColum][indexRow].GetListGameObjectCell());*/
	for (int i = indexRow - 1; i <= indexRow + 1; i++)
	{
		for (int j = indexColumn - 1; j <= indexColumn + 1; j++)
		{
			for (int m = 0; m < cells[i][j].GetListGameObjectCell().size(); m++)
			{
				listGameObjectGrid.push_back(cells[i][j].GetListGameObjectCell().at(m));
			}
			//listGameObjectGrid.push_back(cells[indexColumn][indexRow].GetListGameObjectCell());
		}
	}

}


void Grid::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;
	else
	{
		sizeOfCell = atoi(tokens[0].c_str());
		numOfColumns = atoi(tokens[1].c_str());
		numOfRows = atoi(tokens[2].c_str());
	}
	
	cells = new LPCELL[numOfColumns];
	for (int i = 0; i < numOfColumns; i++)
	{
		cells[i] = new Cell[numOfRows];
	}
}

void Grid::_PareseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	double x = atof(tokens[1].c_str());
	double y = atof(tokens[2].c_str());


	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	int ani_set_id = atoi(tokens[3].c_str());

	CGameObject* obj = NULL;
	switch (object_type)
	{
		case OBJECT_TYPE_GOOMBA: obj = new CGoomba(OBJECT_TYPE_GOOMBA); break;
		case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
		case OBJECT_TYPE_KOOPAS_GREEN_NORMAL: obj = new CKoopas(OBJECT_TYPE_KOOPAS_GREEN_NORMAL); break;
		case OBJECT_TYPE_BOBJECT: obj = new CBackgroundObject(); break;
		case OBJECT_TYPE_FIRST_WORD:
			obj = new CBackgroundObject(OBJECT_TYPE_FIRST_WORD);
			break;
		case OBJECT_TYPE_SECOND_WORD:
			obj = new CBackgroundObject(OBJECT_TYPE_SECOND_WORD);
			break;
		case OBJECT_TYPE_THIRD_WORD_ITEM:
			obj = new CBackgroundObject(OBJECT_TYPE_THIRD_WORD_ITEM);
			break;
		case OBJECT_TYPE_QUESTION: obj = new CQuestion(); break;
		case OBJECT_TYPE_PIPE:	obj = new CPipe(); break;
		case OBJECT_TYPE_COLORBRICK: obj = new CColorBrick(); break;
		case OBJECT_TYPE_COIN:	obj = new CCoin(); break;
		case OBJECT_TYPE_FIREBALL:	obj = new CFireBall(); break;
		case OBJECT_TYPE_ITEM:	obj = new CItem(); break;
		case OBJECT_TYPE_FLOWER: obj = new CFlower(); break;
		case OBJECT_TYPE_FIREFLOWER: obj = new CFireFlower(); break;
		case OBJECT_TYPE_BREAKABLEBRICK: obj = new CBreakableBrick(); break;
		case OBJECT_TYPE_PLETTER: obj = new CPLetter(); break;
		case OBJECT_TYPE_COINQUESTION: obj = new CCoinQuestion(); break;
		case OBJECT_TYPE_KOOPAS_GREEN_FLYING: obj = new CKoopas(OBJECT_TYPE_KOOPAS_GREEN_FLYING); break;
		case OBJECT_TYPE_KOOPAS_RED_NORMAL: obj = new CKoopas(OBJECT_TYPE_KOOPAS_RED_NORMAL); break;
		case OBJECT_TYPE_GOOMBA_FLYING:	obj = new CGoomba(OBJECT_TYPE_GOOMBA_FLYING); break;
		/*case OBJECT_TYPE_FINAL_CARD:
		obj = new CCard();
		break;*/
	}



	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	if (obj != NULL)
	{
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		listGameObjectGrid.push_back(obj);
		int indexRow = x / sizeOfCell;
		int indexColumn = (y+400) / sizeOfCell;
		if (indexRow < numOfRows && indexColumn < numOfColumns)
		{
			cells[indexRow][indexColumn].AddObjectIntoCell(listGameObjectGrid.at(listGameObjectGrid.size() - 1));
		}
	}
}

Grid::~Grid()
{
	//for (int i = 0; i < numOfColumns; i++)
	//{
	//	for (int j = 0; j < numOfRows; i++)
	//	{
	//		
	//		//cells[i][j] = null;
	//	}
	//}
	delete cells;
	cells = NULL;
}
