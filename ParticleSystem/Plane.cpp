#include "Plane.h"
#include <glut.h>
#include <svl\SVLgl.h>
#include "Contact.h"

Plane::Plane(Vec3 normal, Vec3 position)
{
	this->normal = norm(normal);
	this->position = position;
	v1 = normal + Vec3(1.0, 0.0, 0.0);
	v2 = norm(cross(v1, normal));
	v1 = norm(cross(v2, normal));
}

Plane::~Plane(void)
{
}

Vec3 Plane::GetRestoringForce(Vec3 point)
{
	return -normal * GetDistanceTo(point);
}

Contact * Plane::GetContact(Vec3 point)
{
	Contact * contact = new Contact();
	contact->Point = point - dot(normal, point) * normal;
	contact->Normal = normal;
	return contact;
}

void Plane::Draw()
{
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex(position);
		glVertex(position + v1);
		glColor3f(0.0, 1.0, 0.0);
		glVertex(position);
		glVertex(position + v2);
		glColor3f(0.0, 0.0, 1.0);
		glVertex(position);
		glVertex(position + normal);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.5, 0.5, 0.0);
		glVertex(position + (v1 - v2) * 100.0f);
		glVertex(position + (v1 + v2) * 100.0f);
		glVertex(position + (-v1 + v2) * 100.0f);
		glVertex(position + (-v1 - v2) * 100.0f);
	glEnd();
}
