#include "ParticleSystem.h"
#include "ColouredParticle.h"
#include "PhysicsSystem.h"
#include "ICollidable.h"
#include <cstdlib>
#include <glut.h>

ColouredParticleSystem::ColouredParticleSystem(Vec3 position, Vec3 velocity, Vec3 colour, int particleNum, float creationRate)
{
	this->position = position;
	this->velocity = velocity;
	this->colour = colour;
	this->particleNum = particleNum;
	particleLifetime = (int)((particleNum / creationRate) * 1000);
	particleCounter = 0;
	msTimeBetweenSpawn = (int)(1000.0f / creationRate);
	msCounter = 0;
	particles.reserve(particleNum);
}

ColouredParticleSystem::~ColouredParticleSystem(void)
{
}

Vec3 ColouredParticleSystem::RandomVector(float maxLength)
{
	float length = rand() / (float)RAND_MAX;
	length *= maxLength;
	Vec3 vec = Vec3(rand() / (float)RAND_MAX - 0.5f, rand() / (float)RAND_MAX - 0.5f, rand() / (float)RAND_MAX - 0.5f);
	norm(vec);
	vec *= length;
	return vec;
}

void ColouredParticleSystem::Update(float msSinceLast)
{
	msCounter += (int)msSinceLast;
	if (msCounter > msTimeBetweenSpawn)
	{
		for (int i = 0; i < (int)(msCounter / msTimeBetweenSpawn); ++i)
		{
			CreateParticle();
		}
		msCounter = 0;		
	}
	for (int i = 0; i < particles.size(); ++i)
	{	
		particles[i]->AddForce(particles[i]->GetVelocity() * -0.001f); //drag/friction
		particles[i]->AddForce(Vec3(0.0, -0.01f, 0.0));
		ICollidable * coll;
		if (coll = PhysicsSystem::GetCurrentInstance()->CollideWith(particles[i]->GetPosition()))
		{
			//TODO cancel force parallel to plane normal
			particles[i]->AddForce(coll->GetRestoringForce(particles[i]->GetPosition()) * 1.0f);
		}
		particles[i]->Update(msSinceLast);
	}
}

void ColouredParticleSystem::CreateParticle()
{
	Vec3 pos = position + RandomVector(0.3f);
	Vec3 vel = velocity + RandomVector(0.1f);
	ColouredParticle* cp;
	if (particles.size() < particleNum)
	{
		cp = new ColouredParticle();		
		particles.push_back(cp);
	}		
	else
	{
		cp = particles[particleCounter];
		++particleCounter;
		if (particleCounter >= particles.size())
			particleCounter = 0;
	}
	cp->Initialise(pos, vel, 1.0f, particleLifetime);
	cp->Colour = colour + RandomVector(0.05f);
}

void ColouredParticleSystem::Draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(3.0f);
	for (int i = 0; i < particles.size(); ++i)
	{
		glBegin(GL_POINTS);
		particles[i]->Draw();
		glEnd();
	}
}
