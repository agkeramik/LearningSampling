#pragma once
#include "Furniture.h"
#include <vector>
#include <ostream>

class Scene
{
public:
	Scene();
	std::vector<Furniture*> furnitures;
    void print(std::ostream &out);
	virtual ~Scene();
};

