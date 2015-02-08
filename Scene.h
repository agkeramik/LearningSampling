#pragma once
#include "Furniture.h"
#include <vector>
class Scene
{
public:
	Scene();
	std::vector<Furniture*> furnitures;
	virtual ~Scene();
};

