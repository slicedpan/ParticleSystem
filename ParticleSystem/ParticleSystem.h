#pragma once

#include <vector>
#include <svl\SVL.h>

class ColouredParticle;

class ColouredParticleSystem
{
public:
	ColouredParticleSystem(Vec3 position, Vec3 velocity, Vec3 colour, int particleNum, float creationRate);
	~ColouredParticleSystem(void);
	void Update(float msSinceLast);
	void Draw();
private:
	std::vector<ColouredParticle*> particles;
	Vec3 position, velocity, colour;
	int particleNum;
	int msCounter;
	float msTimeBetweenSpawn;
	void CreateParticle();
	Vec3 RandomVector(float maxLength);
	int particleLifetime;
	int particleCounter;
};

