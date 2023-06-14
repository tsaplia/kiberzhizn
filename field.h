#pragma once

#include "animal.h"

enum class SurfaceTypes { water, earth };

class Field
{
public:
    Field(int width, int height);
    ~Field();
    int Width();
    int Height();
    void AddAnimal(int x, int y);
    void AddAnimal(int x, int y, Animal* animal);
    Animal* GetAnimal(int x, int y);
    void KillAnimal(int x, int y);
    void KillAnimal(Animal* animal);
    void UpdatePosition(Animal* animal, int x, int y);
    SurfaceTypes getSurface(int x, int y);
    bool IsInside(int x, int y);

private:
    int m_water_level;
    int m_width;
    int m_height;
    std::vector<std::vector<Animal*>> m_animals;
    std::map<Animal*, std::pair<int, int>> m_animal_list;
};