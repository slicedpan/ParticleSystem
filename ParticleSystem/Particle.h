#pragma once

#include "svl/svl.h"

class Particle
{
public:
	Particle(Vec3 position, Vec3 velocity, float mass);
	~Particle(void);
	void AddForce(Vec3 forceVector);
	inline Vec3 GetVelocity()
	{
		return velocity;
	}
	virtual void Update(float msElapsed);
	inline Vec3 GetPosition()
	{
		return position;
	}
protected:
	Vec3 position;
	Vec3 velocity;
	float mass;
	Vec3 forceAccumulation;
private:
	
};

