#include "Particle.h"

Particle::Particle(Vec3 position, Vec3 velocity, float mass)
{
	this->position = position;
	this->velocity = velocity;
	this->mass = mass;
}

Particle::~Particle(void)
{
}

inline Vec3 Particle::GetPosition()
{
	return position;
}

inline Vec3 Particle::GetVelocity()
{
	return velocity;
}

void Particle::AddForce(Vec3 forceVector)
{
	forceAccumulation += forceVector;
}

void Particle::Update(float msElapsed)
{
	velocity += forceAccumulation / mass;
	position += velocity;
	forceAccumulation.MakeZero();
}
