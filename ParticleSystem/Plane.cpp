#include "Plane.h"
#include <glut.h>
#include <svl\SVLgl.h>

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

inline float Plane::GetDistanceTo(Vec3 point)
{
	point -= position;
	return dot(point, normal);
}

inline Vec3 Plane::GetNormal()
{
	return normal;
}

inline bool Plane::PointIntersects(Vec3 point)
{
	return (GetDistanceTo(point) < 0.0);
}

inline bool Plane::PointWithinDistance(Vec3 point, float dist)
{
	return (fabs(GetDistanceTo(point)) < dist);
}

Vec3 Plane::GetRestoringForce(Vec3 point)
{
	return -normal * GetDistanceTo(point);
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
