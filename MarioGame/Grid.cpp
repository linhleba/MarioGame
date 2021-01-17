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

void Grid::HandleGrid(vector<LPGAMEOBJECT>* coObjects, double camX, double camY, double screenWidth, double screenHeight)
{

	int indexLeftRow = max(0,camX / sizeOfCell);
	int indexRightRow = min(numOfRows - 1, (camX + screenWidth) / sizeOfCell);
	int indexTopColumn = max(0,(camY) / sizeOfCell);
	int indexBottomColumn = min(numOfColumns - 1, (camY + screenHeight) / sizeOfCell);

	if (indexLeftRow == currentLeftRow && indexRightRow == currentRightRow
		&& indexTopColumn == currentTopColumn && indexBottomColumn == currentTopColumn)
		return;

	currentLeftRow = indexLeftRow;
	currentRightRow = indexRightRow;
	currentTopColumn = indexTopColumn;
	currentBottomColumn = indexBottomColumn;
	//coObjects->clear();

	//DebugOut(L"screen witdh la %f \n", screenWidth);

	for (int i = indexLeftRow; i <= indexRightRow; i++)
	{
		for (int j = indexTopColumn; j <= indexBottomColumn; j++)
		{
			if (!cells[i][j].GetListGameObjectCell().empty())
			{
				for (int m = 0; m < cells[i][j].GetListGameObjectCell().size(); m++)
				{
					LPGAMEOBJECT objInCell = cells[i][j].GetListGameObjectCell().at(m);
					if (objInCell->GetIsActive() == false)
					{
						
						// xet neu obj do la di chuyen thi moi du dieu kien reset
						if (objInCell->GetIsStaticObject() == false)
						{

							// neu vi tri cua origin no dang o ngoai cam va obj dang o trang thai active
							if (!((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->CheckForResetObject(objInCell->GetOriginX(), objInCell->GetOriginY()))
							{
								objInCell->Reset();
							}
						}
						coObjects->emplace_back(cells[i][j].GetListGameObjectCell().at(m));
						cells[i][j].GetListGameObjectCell().at(m)->SetIsActive(true);
					}
				}
			}
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
		numOfRows = atoi(tokens[1].c_str());
		numOfColumns = atoi(tokens[2].c_str());
	}
	
	cells = new LPCELL[numOfRows];
	for (int i = 0; i < numOfRows; i++)
	{
		cells[i] = new Cell[numOfColumns];
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
		case OBJECT_TYPE_FLOWER_BIG: obj = new CFlower(OBJECT_TYPE_FLOWER_BIG); break;
		case OBJECT_TYPE_FLOWER_SMALL: obj = new CFlower(OBJECT_TYPE_FLOWER_SMALL); break;
		case OBJECT_TYPE_FIREFLOWER: obj = new CFireFlower(); break;
		case OBJECT_TYPE_BREAKABLEBRICK: obj = new CBreakableBrick(); break;
		case OBJECT_TYPE_PLETTER: obj = new CPLetter(); break;
		case OBJECT_TYPE_COINQUESTION: obj = new CCoinQuestion(); break;
		case OBJECT_TYPE_KOOPAS_GREEN_FLYING: obj = new CKoopas(OBJECT_TYPE_KOOPAS_GREEN_FLYING); break;
		case OBJECT_TYPE_KOOPAS_RED_NORMAL: obj = new CKoopas(OBJECT_TYPE_KOOPAS_RED_NORMAL); break;
		case OBJECT_TYPE_GOOMBA_FLYING:	obj = new CGoomba(OBJECT_TYPE_GOOMBA_FLYING); break;
		case OBJECT_TYPE_PIPE_DOWNING:
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
			break;

		/*case OBJECT_TYPE_SCORE:
			obj = new CScore();
			score = (CScore*)obj;
			break;*/
		case OBJECT_TYPE_FINAL_CARD:
		obj = new CCard();
		break;
	}



	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	if (obj != NULL)
	{
		obj->originX = x;
		obj->originY = y;
		obj->SetPosition(x, y);
		obj->SetOriginPosition(x, y);
		obj->SetAnimationSet(ani_set);
		//.emplace_back(obj);
		int indexRow = x / sizeOfCell;
		int indexColumn = (y) / sizeOfCell;
		if (indexRow < numOfRows && indexColumn < numOfColumns)
		{
			//cells[indexRow][indexColumn].AddObjectIntoCell(listGameObjectGrid.at(listGameObjectGrid.size() - 1));
			cells[indexRow][indexColumn].AddObjectIntoCell(obj);
		}
	}
}

void Grid::UpdateCell()
{

}

Grid::~Grid()
{
	for (size_t i = 0; i < numOfRows; i++)
	{
		for (size_t j = 0; j < numOfColumns; j++)
		{
			cells[i][j].GetListGameObjectCell().clear();
		}
	}
	delete cells;
	cells = NULL;
}
