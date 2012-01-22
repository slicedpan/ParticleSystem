#pragma once

#include "svl/svl.h"

class AABB;
class Sphere;

class ICollidable
{
public:
	virtual bool PointIntersects(Vec3 point) = 0;
	virtual bool PointWithinDistance(Vec3 point, float dist) = 0;	
	virtual Vec3 GetRestoringForce(Vec3 point) = 0;
};

