#pragma once

#include <vector>
#include "SFML\System\Vector2.hpp"
#include "SFML\System\Vector3.hpp"

class Model
{
public:
	Model(std::vector<sf::Vector3f> vertices, sf::Vector3f colour, int id);
	~Model();

	void draw(sf::Vector3f position, sf::Vector3f direction);

	int getId();

private:
	int id;
	sf::Vector3f colour;
	std::vector<sf::Vector3f> vertices;
};

