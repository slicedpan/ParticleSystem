#pragma once

#include "svl/svl.h"

class AABB;
class Sphere;

class ICollidable
{
public:
	virtual bool PointIntersects(Vec3 point) = 0;
	virtual bool Intersects(Sphere* other) = 0;	
};

