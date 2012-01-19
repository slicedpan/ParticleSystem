#include "ColouredParticle.h"
#include "glut.h"

ColouredParticle::ColouredParticle() : Particle(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f)
{
	this->Colour = Vec3(1.0f, 1.0f, 1.0f);
	this->alpha = 0.0f;
	this->lifetime = 16.0f;
	this->currentLifetime = lifetime;
}

ColouredParticle::~ColouredParticle(void)
{
}

void ColouredParticle::Initialise(Vec3 position, Vec3 velocity, float mass, int lifetime)
{
	this->position = position;
	this->velocity = velocity;
	this->mass = mass;
	this->lifetime = lifetime;
	this->currentLifetime = lifetime;
	this->alpha = 1.0f;
}

void ColouredParticle::Update(float msElapsed)
{
	if (alpha > 0.0f)
	{
		currentLifetime -= msElapsed;
		this->alpha = (float)currentLifetime / lifetime;
		Particle::Update(msElapsed);
	}
}

inline bool ColouredParticle::IsRecyclable()
{
	return (alpha >= 0.0f);
}
