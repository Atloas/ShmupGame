#include "Utils.h"

#include <cmath>

sf::Vector2f Utils::normalizeVector(sf::Vector2f input)
{
	float x = input.x, y = input.y;
	float length = std::sqrt(x*x + y*y);
	if (length < 1e-12f)
		return sf::Vector2f();
	return input / length;
}

sf::Vector3f Utils::normalizeVector(sf::Vector3f input)
{
	float x = input.x, y = input.y, z = input.z;
	float length = std::sqrt(x*x + y*y + z*z);
	if (length < 1e-12f)
		return sf::Vector3f();
	return input / length;
}

//Returns RADIANS, glRotatef takes DEGREES
float Utils::getAngleFromUpwards(sf::Vector2f input)
{
	if (fabs(input.x) < 1e-6f && fabs(input.y) < 1e-6f)		//Zero vector
		return 0.0f;

	sf::Vector2f upwards;
	upwards.x = 0.0f;
	upwards.y = 1.0f;
	float dotProduct = vectorDotProcuct2(input, upwards);
	if (fabs(dotProduct) < 1e-6f)							//If the vectors are perpendicular
	{
		if (input.x < 0)
			return 3.1416f/2.0f;
		else
			return -3.1416f/2.0f;
	}

	float inputLength = vectorLength2(input);
	float result = acos(dotProduct/inputLength);
	if (input.x > 0)
		return -result;
	else
		return result;
}


//Might be wrong
float Utils::getAngleFromVector(sf::Vector2f inputA, sf::Vector2f inputB)
{
	float angleA = getAngleFromUpwards(inputA);
	float angleB = getAngleFromUpwards(inputB);

	float result = -(angleA - angleB);

	return result;
}

float Utils::convertToRadian(float input)
{
	return input*3.1416f/180.0f;
}

float Utils::convertToDegrees(float input)
{
	return input*180.0f/3.1416f;
}

float Utils::vectorLength2(sf::Vector2f input)
{
	return sqrt(input.x*input.x + input.y*input.y);
}

float Utils::vectorLength2(sf::Vector3f input)
{
	return sqrt(input.x*input.x + input.y*input.y);
}

float Utils::vectorLength3(sf::Vector3f input)
{
	return sqrt(input.x*input.x + input.y*input.y + input.z*input.z);
}

float Utils::vectorDotProcuct2(sf::Vector2f inputA, sf::Vector2f inputB)
{
	return inputA.x*inputB.x + inputA.y*inputB.y;
}

float Utils::vectorDotProcuct2(sf::Vector3f inputA, sf::Vector3f inputB)
{
	return inputA.x*inputB.x + inputA.y*inputB.y;
}

float Utils::vectorDotProcuct3(sf::Vector3f inputA, sf::Vector3f inputB)
{
	return inputA.x*inputB.x + inputA.y*inputB.y + inputA.z*inputB.z;
}

void Utils::sortEffectVectorByHeight(std::vector<Effect*>& input)
{
	unsigned int size = input.size();
	for (unsigned int i = 1; i < input.size(); i++)
	{
		Effect* temp = input.at(i);
		int j = i - 1;
		for (; j >= 0 && input.at(j)->getHeight() > temp->getHeight(); j--)
		{
			swap(input.at(j + 1), input.at(j));
		}
		input.at(j + 1) = temp;
	}
}

Utils::Utils()
{

}


Utils::~Utils()
{

}
