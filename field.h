#pragma once

#include <vector>
#include <map>
#include "animal.h"

class Field
{
public:
	Field(int width,int height);
	int Width();
	int Height();
	void AddAnimal(int x, int y);
	Animal* GetAnimal(int x, int y);
	void KillAnimal(int x, int y);
	void KillAnimal(Animal* animal);
	void UpdatePosition(Animal* animal, int x, int y);
private:
	int m_width;
	int m_height;
	std::vector<std::vector<Animal*>> m_animals;
	std::map<Animal*, std::pair<int,int>> m_animal_list;
};

