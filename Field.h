#pragma once

#include <SFML\System\Vector2.hpp>
#include <SFML\System\Vector3.hpp>

class Field
{
public:
	Field(float xMin, float xMax, float yMin, float yMax);
	~Field();

	bool checkIfInside(sf::Vector2f position);

	sf::Vector2f clampVector(sf::Vector2f input);
	sf::Vector3f clampVector(sf::Vector3f input);

	float getXMin();
	float getXMax();
	float getYMin();
	float getYMax();

private:
	float xMin, xMax, yMin, yMax;
};

