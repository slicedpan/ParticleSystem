#pragma once

class ICollidable;
struct Contact;

#include <vector>
#include <svl\SVL.h>

class PhysicsSystem
{
public:
	~PhysicsSystem(void);
	static PhysicsSystem * GetCurrentInstance();
	void AddCollidable(ICollidable* obj);
	ICollidable* CollideWith(Vec3 point);
private:
	static PhysicsSystem * currentInstance;
	std::vector<ICollidable*> collidables;
	PhysicsSystem(void);
};

