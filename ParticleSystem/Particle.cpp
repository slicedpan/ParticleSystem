#include "Particle.h"

Particle::Particle(Vec3 position, Vec3 velocity, float mass)
{
	this->position = position;
	this->velocity = velocity;
	this->mass = mass;
	this->forceAccumulation.MakeZero();
}

Particle::~Particle(void)
{
}

void Particle::AddForce(Vec3 forceVector)
{
	forceAccumulation += forceVector;
}

void Particle::Update(float msElapsed)
{
	velocity += forceAccumulation / mass;
	position += velocity;
	ClearForces();
}
