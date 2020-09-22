#include "Field.h"

Field::Field(float xMin, float xMax, float yMin, float yMax)
{
	this->xMin = xMin;
	this->xMax = xMax;
	this->yMin = yMin;
	this->yMax = yMax;
}

Field::~Field()
{
}

bool Field::checkIfInside(sf::Vector2f position)
{
	return position.x >= xMin && position.x <= xMax && position.y >= yMin && position.y <= yMax;
}

sf::Vector2f Field::clampVector(sf::Vector2f input)
{
	if (input.x < xMin)
		input.x = xMin;
	else if (input.x > xMax)
		input.x = xMax;

	if (input.y < yMin)
		input.y = yMin;
	else if (input.y > yMax)
		input.y = yMax;

	return input;
}

sf::Vector3f Field::clampVector(sf::Vector3f input)
{
	if (input.x < xMin)
		input.x = xMin;
	else if (input.x > xMax)
		input.x = xMax;

	if (input.y < yMin)
		input.y = yMin;
	else if (input.y > yMax)
		input.y = yMax;

	return input;
}

float Field::getXMin()
{
	return xMin;
}

float Field::getXMax()
{
	return xMax;
}

float Field::getYMin()
{
	return yMin;
}

float Field::getYMax()
{
	return yMax;
}
