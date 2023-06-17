#pragma once

#include <QtCore>
#include <QColor>
#include "network_of_nodes.h"
#include "config.h"

class Field; 

enum AnimalDirections { left, up, right, down };

class Animal
{
public:
    Animal(int x, int y, Field* parent);
    Animal(int x, int y, Field* parent, NetworkOfNodes* brain, QColor color);
    ~Animal();
    void Motion();
    QColor GetLifeColor();
    QColor GetFamilyColor();
    QColor GetEnergyColor();
    QColor GetAgeColor();

    static void SetColorsInMoution(int value);

private:
    void InitEmpty(int x, int y, Field* parent);
    std::pair<int, int> LooksAt();
    bool CanMove();
    bool CanAttack();
    bool CanSynthesize();
    bool CanReproduce();
    void Attack();
    void Move();
    void Photosynthesis();
    void Reproduction();
    std::vector<double> GetBrainInput();
    static Animal* Mutation(Animal* animal);

    int m_x;
    int m_y;
    int m_energy;
    int m_age;
    QColor m_color;
    Field* m_parent;
    NetworkOfNodes* m_brain;
    AnimalDirections m_direction;
    int m_attacks_cnt;
    int m_synthesis_cnt;

    inline static int m_colors_in_moution = 10;
    inline static int m_mutation_probabilyty = 5;
};