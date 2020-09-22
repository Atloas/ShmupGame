#pragma once

#include <SFML\System\Vector3.hpp>
#include <SFML\System\Vector2.hpp>

#include <vector>

#include "Field.h"
#include "Effect.h"

class Utils
{
public:

	static sf::Vector2f normalizeVector(sf::Vector2f input);
	static sf::Vector3f normalizeVector(sf::Vector3f input);

	static float getAngleFromUpwards(sf::Vector2f input);
	static float getAngleFromVector(sf::Vector2f inputA, sf::Vector2f inputB);

	static float convertToRadian(float input);
	static float convertToDegrees(float input);

	static float vectorLength2(sf::Vector2f input);
	static float vectorLength2(sf::Vector3f input);
	static float vectorLength3(sf::Vector3f input);

	static float vectorDotProcuct2(sf::Vector2f inputA, sf::Vector2f inputB);
	static float vectorDotProcuct2(sf::Vector3f inputA, sf::Vector3f inputB);
	static float vectorDotProcuct3(sf::Vector3f inputA, sf::Vector3f inputB);

	static void sortEffectVectorByHeight(std::vector<Effect*> &input);
	
	template<typename T> static T clampValue(T input, T lower, T upper);
	template<typename T> static bool checkIfVectorContains(std::vector<T> input, T target);
	template<typename T> static void swap(T &a, T &b);


private:
	Utils();
	~Utils();
};

template<typename T>
inline T Utils::clampValue(T input, T lower, T upper)
{
	if(input < lower)
		return lower;
	if (input > upper)
		return upper;
	return input;
}

template<typename T>
inline bool Utils::checkIfVectorContains(std::vector<T> input, T target)
{
	for (unsigned int i = 0; i < input.size(); i++)
	{
		if (input.at(i) == target)
			return true;
	}
	return false;
}

template<typename T>
inline void Utils::swap(T & a, T & b)
{
	T temp = b;
	b = a;
	a = temp;
}
