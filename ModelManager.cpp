#include "ModelManager.h"

#include "OBJECT_ID.h"

std::vector<Model> ModelManager::models;

Model& ModelManager::getModel(int id)
{
	for (unsigned int i = 0; i < models.size(); i++)
	{
		if (models.at(i).getId() == id)
			return models.at(i);
	}
	return Model(std::vector<sf::Vector3f>(), sf::Vector3f(), -1);
}

void ModelManager::generateModels()
{
	std::vector<sf::Vector3f> vertices;
	sf::Vector3f colour;

	//PLAYER
	vertices.push_back(sf::Vector3f(0.0f, 0.0f, 0.0f));
	vertices.push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
	vertices.push_back(sf::Vector3f(-0.5f, -0.5f, 0.0f));
	vertices.push_back(sf::Vector3f(0.0f, 0.0f, 0.0f));
	vertices.push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
	vertices.push_back(sf::Vector3f(0.5f, -0.5f, 0.0f));
	colour = sf::Vector3f(0.1f, 0.5f, 0.1f);
	models.push_back(Model(vertices, colour, OBJECT_ID::PLAYER));
	vertices.clear();

	//ENEMY_PLANE
	vertices.push_back(sf::Vector3f(0.0f, 0.0f, 0.0f));
	vertices.push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
	vertices.push_back(sf::Vector3f(-0.5f, -0.5f, 0.0f));
	vertices.push_back(sf::Vector3f(0.0f, 0.0f, 0.0f));
	vertices.push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
	vertices.push_back(sf::Vector3f(0.5f, -0.5f, 0.0f));
	colour = sf::Vector3f(0.5f, 0.5f, 0.5f);
	models.push_back(Model(vertices, colour, OBJECT_ID::ENEMY_PLANE));
	vertices.clear();

	//PLAYER_BULLET
	vertices.push_back(sf::Vector3f(0.0f, 0.5f, 0.0f));
	vertices.push_back(sf::Vector3f(0.15f, 0.0f, 0.0f));
	vertices.push_back(sf::Vector3f(-0.15f, 0.0f, 0.0f));
	colour = sf::Vector3f(0.9f, 0.9f, 0.2f);
	models.push_back(Model(vertices, colour, OBJECT_ID::PLAYER_BULLET));
	vertices.clear();

	//ENEMY_BULLET
	vertices.push_back(sf::Vector3f(0.0f, 0.5f, 0.0f));
	vertices.push_back(sf::Vector3f(0.15f, 0.0f, 0.0f));
	vertices.push_back(sf::Vector3f(-0.15f, 0.0f, 0.0f));
	colour = sf::Vector3f(1.0f, 0.3f, 0.3f);
	models.push_back(Model(vertices, colour, OBJECT_ID::ENEMY_BULLET));
	vertices.clear();

	//ENEMY_BOAT
	vertices.push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
	vertices.push_back(sf::Vector3f(-1.0f, 0.0f, 0.0f));
	vertices.push_back(sf::Vector3f(1.0f, 0.0f, 0.0f));
	vertices.push_back(sf::Vector3f(-1.0f, 0.0f, 0.0f));
	vertices.push_back(sf::Vector3f(1.0f, 0.0f, 0.0f));
	vertices.push_back(sf::Vector3f(-1.0f, -2.0f, 0.0f));
	vertices.push_back(sf::Vector3f(1.0f, 0.0f, 0.0f));
	vertices.push_back(sf::Vector3f(1.0f, -2.0f, 0.0f));
	vertices.push_back(sf::Vector3f(-1.0f, -2.0f, 0.0f));
	colour = sf::Vector3f(0.33f, 0.33f, 0.33f);
	models.push_back(Model(vertices, colour, OBJECT_ID::ENEMY_BOAT));
	vertices.clear();

	//ENEMY_TURRET
	vertices.push_back(sf::Vector3f(-0.25f, 0.5f, 0.0f));
	vertices.push_back(sf::Vector3f(0.25f, 0.5f, 0.0f));
	vertices.push_back(sf::Vector3f(0.25f, 1.5f, 0.0f));
	vertices.push_back(sf::Vector3f(-0.25f, 0.5f, 0.0f));
	vertices.push_back(sf::Vector3f(-0.25f, 1.5f, 0.0f));
	vertices.push_back(sf::Vector3f(0.25f, 1.5f, 0.0f));
	vertices.push_back(sf::Vector3f(-0.5f, 0.5f, 0.0f));
	vertices.push_back(sf::Vector3f(0.5f, 0.5f, 0.0f));
	vertices.push_back(sf::Vector3f(0.5f, -0.5f, 0.0f));
	vertices.push_back(sf::Vector3f(-0.5f, 0.5f, 0.0f));
	vertices.push_back(sf::Vector3f(-0.5f, -0.5f, 0.0f));
	vertices.push_back(sf::Vector3f(0.5f, -0.5f, 0.0f));
	colour = sf::Vector3f(0.425f, 0.425f, 0.425f);
	models.push_back(Model(vertices, colour, OBJECT_ID::ENEMY_TURRET));
	vertices.clear();
}

ModelManager::ModelManager()
{
}


ModelManager::~ModelManager()
{
}
