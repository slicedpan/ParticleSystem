#pragma once
#include "iforcefield.h"
#include <svl\SVL.h>

class CentralForce : public IForceField
{
public:
	CentralForce(Vec3 centre, float strength);
	~CentralForce(void);
	void ApplyForce(Particle* particle);	
private:
	Vec3 centre;
	float strength;
};

