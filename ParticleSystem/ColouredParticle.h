#pragma once

#include "Particle.h"

class ColouredParticle : public Particle
{
public:
	ColouredParticle();
	~ColouredParticle(void);
	void Update(float msElapsed);
	Vec3 Colour;
	void Initialise(Vec3 position, Vec3 velocity, float mass, int lifetime);
	inline bool IsRecyclable()
	{
		return (alpha >= 0.0f);
	}
	void Draw();
private:
	float alpha;
	int lifetime;
	int currentLifetime;
};

