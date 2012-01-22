#include "PhysicsSystem.h"
#include "ICollidable.h"

PhysicsSystem * PhysicsSystem::currentInstance;


PhysicsSystem::PhysicsSystem(void)
{
}

PhysicsSystem::~PhysicsSystem(void)
{
}

PhysicsSystem* PhysicsSystem::GetCurrentInstance()
{
	if (currentInstance == 0)
		currentInstance = new PhysicsSystem();
	return currentInstance;
}

void PhysicsSystem::AddCollidable(ICollidable* obj)
{
	collidables.push_back(obj);
}

ICollidable* PhysicsSystem::CollideWith(Vec3 point)
{
	for (int i = 0; i < collidables.size(); ++i)
	{
		if (collidables[i]->PointIntersects(point))
			return collidables[i];
	}
	return 0;
}
