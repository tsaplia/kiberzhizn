#include "animal.h"

const int DEFAULT_ENERGY = 200;
const int PHOTOSYNTHESIS_ENERGY = 20;

Animal::Animal(int x, int y, Field* parent) {
	m_direction = AnimalDirections::up;
	m_x = x;
	m_y = y;
	m_energy = DEFAULT_ENERGY;
	m_parent = parent;
}

Animal::~Animal() {
	
}

std::pair<int, int> Animal::CalcNextPosition() {
	int x = m_x, y = m_y;
	switch (m_direction)
	{
	case AnimalDirections::down:
		if (m_y < m_parent->Height()) y++;
		break;
	case AnimalDirections::left:
		if (m_x >= 0) x--;
		break;
	case AnimalDirections::right:
		if (m_x < m_parent->Width()) x++;
		break;
	case AnimalDirections::up:
		if (m_y >= 0) y--;
		break;
	}
	return { x,y };
}

void Animal::Move() {
	std::pair<int, int> pos = CalcNextPosition();
	m_x = pos.first, m_y = pos.second;
	m_parent->UpdatePosition(this, m_x, m_y);
}

void Animal::Photosynthesis() {
	m_energy += DEFAULT_ENERGY;
}

void Animal::Atack() {
	std::pair<int, int> pos = CalcNextPosition();
	if (pos.first != m_x || pos.second != m_y) {
		m_parent->KillAnimal(pos.first, pos.second);
	}
}

void Animal::Motion() {

}

