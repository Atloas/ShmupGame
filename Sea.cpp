#include "Sea.h"

#include <SFML\OpenGL.hpp>
#include <cstdlib>

Sea::Sea(Field *field, unsigned int width, unsigned int height)
{
	xMin = field->getXMin();
	xMax = field->getXMax();
	yMin = field->getYMin();
	yMax = field->getYMax();

	this->width = width;
	this->height = height;

	timer = 0.0f;

	generateVertices();
}

void Sea::draw()
{
	glBegin(GL_TRIANGLE_STRIP);
	for (unsigned int i = 0; i < vertexDrawOrder.size(); i++)
	{
		sf::Vector3f currentVertex = vertices.at(vertexDrawOrder.at(i));
		float colourMod = calculateColourMod(currentVertex.z);
		glColor3f(0.3f + colourMod, 0.3f + colourMod, 0.65f + colourMod);
		glVertex3f(currentVertex.x, currentVertex.y, currentVertex.z);
	}
	glEnd();
}

void Sea::tick(float frameTime)
{
	timer += frameTime;
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		vertices.at(i).z = calculateVertexHeight(vertices.at(i).x, vertices.at(i).y);
	}
}

void Sea::generateVertices()
{
	float yStep = (yMax - yMin) / (float)(height - 1);
	float xStep = (xMax - xMin) / (float)(width - 1);

	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			float x = xMin + xStep * i;
			float y = yMin + yStep * j;
			vertices.push_back(sf::Vector3f(x, y, 0.0f));
		}
	}

	for (unsigned int x = 0; x < width - 1; x++)
	{
		if (x > 0)
		{
			// Degenerate begin: repeat first vertex
			vertexDrawOrder.push_back(x * height);
		}

		for (unsigned int y = 0; y < height; y++)
		{
			// One part of the strip
			vertexDrawOrder.push_back(x * height + y);
			vertexDrawOrder.push_back((x + 1) * height + y);
		}

		if (x < width - 2)
		{
			// Degenerate end: repeat last vertex
			vertexDrawOrder.push_back((x + 1) * height + height - 1);
		}
	}
}

float Sea::calculateColourMod(float z)
{
	return pow(z, 4)/20.0f;
}

float Sea::calculateVertexHeight(float x, float y)
{
	return sin((x + timer) / 14.0f + (y + timer) / 2.0f);
}
