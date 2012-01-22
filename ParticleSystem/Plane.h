#pragma once

#include "svl/svl.h"
#include "ICollidable.h"

class Plane : public ICollidable
{
public:
	Plane(Vec3 normal, Vec3 position);
	~Plane(void);
	float GetDistanceTo(Vec3 point);
	void Draw();
	Vec3 GetNormal();
	bool PointIntersects(Vec3 point);
	bool PointWithinDistance(Vec3 point, float dist);
	Vec3 GetRestoringForce(Vec3 point);
private:
	Vec3 normal;
	Vec3 position;
	Vec3 v1, v2;
};

