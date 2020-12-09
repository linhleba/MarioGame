#include "NodeList.h"

void CNodeList::Render()
{
}

void CNodeList::GetBoundingBox(double& left, double& top, double& right, double& bottom)
{
}

void CNodeList::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//if (openingGate == true)
	//{
	//	listOfNodes.at(13)->SetDirection(15, VECTOR_INDEX_RIGHT_DIRECTION);
	//}
}

void CNodeList::AddNode(CNode* node)
{
	listOfNodes.push_back(node);
}

void CNodeList::SetTheDirection()
{
	for (size_t i = 0; i < listOfNodes.size(); i++)
	{
		for (size_t j = i + 1; j < listOfNodes.size(); j++)
		{
			double posY1, posX1, posY2, posX2;
			listOfNodes.at(i)->GetPosition(posX1, posY1);
			listOfNodes.at(j)->GetPosition(posX2, posY2);
			// Set the distance of the position to update into the vector direction
			if (abs(posY1 - posY2) <= 300 && posX1 == posX2)
			{
				if (posY1 > posY2)
				{
					listOfNodes.at(i)->SetDirection(listOfNodes.at(j)->GetId(), VECTOR_INDEX_TOP_DIRECTION);
					listOfNodes.at(j)->SetDirection(listOfNodes.at(i)->GetId(), VECTOR_INDEX_BOTTOM_DIRECTION);
				}
				else
				{
					listOfNodes.at(i)->SetDirection(listOfNodes.at(j)->GetId(), VECTOR_INDEX_BOTTOM_DIRECTION);
					listOfNodes.at(j)->SetDirection(listOfNodes.at(i)->GetId(), VECTOR_INDEX_TOP_DIRECTION);
				}
			}

			// Check position in verticla dir
			if (abs(posX1 - posX2) <= 300 && posY1 == posY2)
			{
				if (posX1 > posX2)
				{
					listOfNodes.at(i)->SetDirection(listOfNodes.at(j)->GetId(), VECTOR_INDEX_LEFT_DIRECTION);
					listOfNodes.at(j)->SetDirection(listOfNodes.at(i)->GetId(), VECTOR_INDEX_RIGHT_DIRECTION);
				}
				else
				{
					listOfNodes.at(i)->SetDirection(listOfNodes.at(j)->GetId(), VECTOR_INDEX_RIGHT_DIRECTION);
					listOfNodes.at(j)->SetDirection(listOfNodes.at(i)->GetId(), VECTOR_INDEX_LEFT_DIRECTION);
				}
			}

		}
	}
}

bool CNodeList::FindTheDirection(int dir)
{
	int direction = listOfNodes.at(currentID - 1)->GetDirection(dir);
	if (direction == 0)
	{
		return false;
	}
	else
	{
		currentID = direction;
		return true;
	}
}
