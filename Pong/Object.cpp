#include "Object.h"

ObjectT::ObjectT()
{
}

ObjectT::~ObjectT()
{
}

ObjectF::ObjectF()
{
}

ObjectF::~ObjectF()
{
}

void ObjectF::SetHitBox()
{
	Box.WallX1 = FRect.x; Box.WallX2 = FRect.x + FRect.w;
	Box.WallY1 = FRect.y; Box.WallY2 = FRect.y + FRect.h;
}
