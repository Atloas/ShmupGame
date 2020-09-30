#include "Model.h"

#include <SFML\OpenGL.hpp>

Model::Model(std::vector<sf::Vector3f> vertices, sf::Vector3f colour, int id)
{
	this->vertices = vertices;
	this->colour = colour;
	this->id = id;
}


Model::~Model()
{
}

void Model::draw(sf::Vector3f position, sf::Vector3f direction)
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	const float RADDEG = 57.29578f;
	float directionLength = sqrt(direction.x*direction.x + direction.y*direction.y + direction.z*direction.z);
	//TODO: This might not work
	float azimuth = atan2(direction.y, direction.x) * RADDEG;
	float elevation = asin(direction.z / directionLength) * RADDEG;
	glRotatef(azimuth, 0, 0, 1);
	glRotatef(-elevation, 0, 1, 0);
	//TODO: Don't begin and end every time? Draw everything at once?
	glBegin(GL_TRIANGLES);
	glColor3f(colour.x, colour.y, colour.z);
	for (unsigned int i = 0; i < vertices.size(); ++i)
	{
		sf::Vector3f& currentVertex = vertices.at(i);
		glVertex3f(currentVertex.x, currentVertex.y, currentVertex.z);
	}
	glEnd();
	glPopMatrix();
}

int Model::getId()
{
	return id;
}
