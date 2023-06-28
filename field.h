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
    SurfaceTypes GetSurface(int x, int y);
    int GetAnimalsCnt();
    FieldStats GetStats();
    int GetWaterLavel();
    bool IsInside(int x, int y);
    void Moution();
    void RandGen(int mod);
    void Clear();

private:
    int m_animals_cnt = 0;
    int m_kills_cnt = 0;
    int m_born_cnt = 0;
    int m_water_level;
    int m_width;
    int m_height;
    QSet<Animal*> m_processed;
    std::vector<std::vector<Animal*>> m_animals;
    std::map<Animal*, std::pair<int, int>> m_animal_list;
};