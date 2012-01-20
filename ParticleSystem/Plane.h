#pragma once

#include "svl/svl.h"

class Plane
{
public:
	Plane(Vec3 normal, Vec3 position);
	~Plane(void);
	float GetDistanceTo(Vec3 point);
	void Draw();
	Vec3 GetNormal();
private:
	Vec3 normal;
	Vec3 position;
	Vec3 v1, v2;
};

