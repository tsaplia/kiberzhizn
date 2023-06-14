#pragma once

#include <QtCore>
#include <QColor>
#include "network_of_nodes.h"

class Field; 

enum class AnimalDirections { left, up, right, down };

class Animal
{
public:
    Animal(int x, int y, Field* parent);
    Animal(int x, int y, Field* parent, NetworkOfNodes* brain, QColor color);
    ~Animal();
    void Motion();

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
    QColor m_color;
    Field* m_parent;
    NetworkOfNodes* m_brain;
    AnimalDirections m_direction;
    int m_attacks_cnt;
    int m_synthesis_cnt;
};