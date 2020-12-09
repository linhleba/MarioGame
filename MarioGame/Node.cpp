#include "Node.h"
#include "Utils.h"

void CNode::Render()
{
}

void CNode::GetBoundingBox(double& left, double& top, double& right, double& bottom)
{
}

CNode::CNode(int id)
{
	direction.assign(4, 0);
	this->id = id;
}
