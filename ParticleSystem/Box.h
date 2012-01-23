#pragma once
#include "icollidable.h"

class Box : public ICollidable
{
public:
	Box(Vec3 centre, Vec3 extents);
	~Box(void);
	bool PointIntersects(Vec3& point);
	bool PointWithinDistance(Vec3& point, float dist);
	Contact* GetContact(Vec3& point);
	void Draw();
	Vec3 Colour;
private:
	Vec3 centre;
	Vec3 extents;
	Vec3 max;
	Vec3 min;
};

