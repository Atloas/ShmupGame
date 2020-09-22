#pragma once

#include <vector>
#include <SFML/System/Vector3.hpp>

#include "Field.h"

class Sea
{
public:
	Sea(Field *field, unsigned int width, unsigned int height);

	virtual void draw();
	virtual void tick(float frameTime);

private:
	void generateVertices();
	float calculateColourMod(float z);
	float calculateVertexHeight(float x, float y);

	float xMin, xMax, yMin, yMax;
	unsigned int width, height;
	float timer;
	std::vector<sf::Vector3f> vertices;
	std::vector<int> vertexDrawOrder;
};