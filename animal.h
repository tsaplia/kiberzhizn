#pragma once

#include <QtCore>
#include <QColor>

class Field; 

enum class AnimalDirections { left, up, right, down };

class Animal
{
public:
    Animal(int x, int y, Field* parent, QColor color);
    ~Animal();
    void Motion();

private:
    std::pair<int, int> LooksAt();
    bool CanMove();
    bool CanAttack();
    bool CanSynthesize();
    bool CanReproduce();
    void Attack();
    void Move();
    void Photosynthesis();
    void Reproduction();

    int m_x;
    int m_y;
    int m_energy;
    QColor m_color;
    Field* m_parent;
    AnimalDirections m_direction;
    int m_attacks_cnt;
    int m_synthesis_cnt;
};