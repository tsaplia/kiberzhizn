#pragma once

#include "field.h"

class Animal
{
public:
	Animal(int x, int y, Field* perent);
	~Animal();
	void Motion();
private:
	std::pair<int, int> CalcNextPosition();
	void Atack();
	void Move();
	void Photosynthesis();
	int m_x;
	int m_y;
	int m_energy;
	Field* m_parent;
	AnimalDirections m_direction;
};
enum class AnimalDirections {left,up,right,down};

