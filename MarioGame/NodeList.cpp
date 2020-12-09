#include "NodeList.h"

void NodeList::SetTheDirection()
{
	for (int i = 0; i < sumOfNodes; i++)
	{
		for (int j = i + 1; j < sumOfNodes; j++)
		{
			double posY1 = listOfNodes.at(i)->y;
			double posY2 = listOfNodes.at(j)->y;
			double posX1 = listOfNodes.at(i)->x;
			double posX2 = listOfNodes.at(j)->x;
			// Set the distance of the position to update into the vector direction
			if (abs(posY1 < posY2) <= 300)
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
			if (abs(posX1 < posX2) <= 300)
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

int NodeList::findTheDirection(int dir)
{
	return listOfNodes.at(currentDirectID)->GetDirection(dir);
}
