#pragma once

#include "Model.h"

class ModelManager
{
public:
	static Model getModel(int id);
	static void generateModels();

private:
	ModelManager();
	~ModelManager();

	static std::vector<Model> models;

};

