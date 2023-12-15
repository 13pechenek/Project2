#include "Enemies.h"
#include "Walls.h"


bool Enemies::Overlapped(Walls* wall, ID2D1TransformedGeometry* ray)
{
	D2D1_GEOMETRY_RELATION* relation = new D2D1_GEOMETRY_RELATION;
	ray->CompareWithGeometry(wall->rectangle, NULL, relation);
	if (*relation == D2D1_GEOMETRY_RELATION_DISJOINT) return true;
	else return false;
}