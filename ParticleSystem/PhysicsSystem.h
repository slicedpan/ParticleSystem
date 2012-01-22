#pragma once

class ICollidable;

#include <vector>
#include <svl\SVL.h>

class PhysicsSystem
{
public:
	PhysicsSystem(void);
	~PhysicsSystem(void);
	static PhysicsSystem * GetCurrentInstance();
	void AddCollidable(ICollidable* obj);
	ICollidable* CollideWith(Vec3 point);
private:
	static PhysicsSystem * currentInstance;
	std::vector<ICollidable*> collidables;
};

