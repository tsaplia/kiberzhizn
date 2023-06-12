#include "animal.h"
#include "field.h"

const int DEFAULT_ENERGY = 8;
const int PHOTOSYNTHESIS_ENERGY = 4;
const int KILL_ENERGY = 8;
const int REPRODUCTION_ENERGY = 8;

const std::pair<int, int> LOOKS_AT_BORDER = std::make_pair(-1,-1);


Animal::Animal(int x, int y, Field* parent, QColor color = QColor()) { 
	m_direction = AnimalDirections::up;
	m_x = x;
	m_y = y;
	m_energy = DEFAULT_ENERGY;
	m_parent = parent;
	if (!color.isValid()) {
		srand(time(0));
		color = QColor(rand() % 255, rand() % 255, rand() % 255);
	}
	m_color = color;
	m_attacks_cnt = m_synthesis_cnt = 0;
}

std::pair<int, int> Animal::LooksAt() {
	int x = m_x, y = m_y;
	switch (m_direction)
	{
	case AnimalDirections::down:
		y++;
		break;
	case AnimalDirections::left:
		x--;
		break;
	case AnimalDirections::right:
		x++;
		break;
	case AnimalDirections::up:
		y--;
		break;
	}
	return (m_parent->IsInside(x, y) ? std::make_pair(x, y) : LOOKS_AT_BORDER);
}

bool Animal::CanMove() {
	return LooksAt() != LOOKS_AT_BORDER;
}

void Animal::Move() {
	std::pair<int, int> look = LooksAt();
	m_x = look.first, m_y = look.second;
	m_parent->UpdatePosition(this, m_x, m_y);
}

bool Animal::CanSynthesize() {
	return m_parent->getSurface(m_x, m_y) == SurfaceTypes::earth;
}

void Animal::Photosynthesis() {
	m_energy += PHOTOSYNTHESIS_ENERGY;
	m_attacks_cnt++;
}

bool Animal::CanAttack() {
	std::pair<int, int> look = LooksAt();
	return look != LOOKS_AT_BORDER && m_parent->GetAnimal(look.first, look.second);
}

void Animal::Attack() {
	std::pair<int, int> look = LooksAt();
	m_parent->KillAnimal(look.first, look.second);
	m_energy += KILL_ENERGY;
	m_attacks_cnt++;
}

bool Animal::CanReproduce() {
	std::pair<int, int> look = LooksAt();
	return look != LOOKS_AT_BORDER && !m_parent->GetAnimal(look.first, look.second) && 
		m_energy > REPRODUCTION_ENERGY;
}

void Animal::Reproduction() {
	std::pair<int, int> look = LooksAt();
	m_parent->AddAnimal(look.first, look.second, m_color);
	m_energy -= REPRODUCTION_ENERGY;
}

void Animal::Motion() {

}

Animal::~Animal() {

}

