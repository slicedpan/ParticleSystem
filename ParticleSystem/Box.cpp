#include "Box.h"
#include "Contact.h"
#include <glut.h>
#include <svl\SVLgl.h>

Box::Box(Vec3 centre, Vec3 extents)
{
	this->centre = centre;
	this->extents = extents;
	this->max = centre + (extents / 2.0f);
	this->min = centre - (extents / 2.0f);
	this->Colour = Vec3(0.9, 0.1, 0.0);
}

Box::~Box(void)
{
}

bool Box::PointIntersects(Vec3& point)
{
	if (point[0] > min[0] && point[0] < max[0])
	{
		if (point[1] > min[1] && point[1] < max[1])
		{
			if (point[2] > min[2] && point[2] < max[2])
			{
				return true;
			}
		}
	}
	return false;
}

bool Box::PointWithinDistance(Vec3& point, float dist)
{
	return true; //fix maybe
}

Contact* Box::GetContact(Vec3& point)
{
	Contact* contact = new Contact();
	float minDist = FLT_MAX;
	int side;	
	for (int i = 0; i < 6; ++i)
	{
		int coord = i / 2;
		if (i % 2 == 0)
		{
			if (max[coord] - point[coord] < minDist)
			{
				minDist = max[coord] - point[coord];
				side = i;
				contact->Normal.MakeZero();
				contact->Normal[coord] = 1.0f;
				contact->Point = point - dot(contact->Normal, point) * contact->Normal;
				contact->Point[coord] = max[coord];
			}			
		}
		else
		{
			if (point[coord] - min[coord] < minDist)
			{
				minDist = point[coord] - min[coord];
				side = i;
				contact->Normal.MakeZero();
				contact->Normal[coord] = -1.0f;
				contact->Point = point - dot(contact->Normal, point) * contact->Normal;
				contact->Point[coord] = min[coord];
			}
		}
	}
	return contact;
}

void Box::Draw()
{
	glPushMatrix();
	glTranslatef(centre[0], centre[1], centre[2]);
	glScalef(extents[0], extents[1], extents[2]);
	glColor(Colour);
	glutSolidCube(1.0);
	glPopMatrix();
}
