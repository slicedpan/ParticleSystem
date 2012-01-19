#pragma once

#include "svl/svl.h"

class Particle
{
public:
	Particle(Vec3 position, Vec3 velocity, float mass);
	~Particle(void);
	Vec3 GetPosition();
	void AddForce(Vec3 forceVector);
	Vec3 GetVelocity();
	virtual void Update(float msElapsed);
protected:
	Vec3 position;
	Vec3 velocity;
	float mass;
private:
	Vec3 forceAccumulation;
};

