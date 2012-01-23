#pragma once

#include "IForceField.h"
#include <svl\SVL.h>

class GravitationalForce : public IForceField
{
public:
	GravitationalForce(Vec3 direction);
	~GravitationalForce(void);
	void ApplyForce(Particle* particle);
private:
	Vec3 direction;
};

