#include "field.h"

Field::Field(int width, int height) {
	m_height = height;
	m_width = width;
	m_animals.resize(width, std::vector<Animal*>(height));
}

int Field::Width() {
	return m_width;
}

int Field::Height() {
	return m_height;
}

void Field::AddAnimal(int x, int y) {
	m_animals[x][y] = new Animal(x, y, this);
	m_animal_list[m_animals[x][y]] = { x,y };
}

Animal* Field::GetAnimal(int x, int y) {
	return m_animals[x][y];
}

void Field::KillAnimal(int x, int y) {
	if(!(m_animals[x][y])) return;

	m_animal_list.erase(m_animals[x][y]);
	delete m_animals[x][y];
	m_animals[x][y] = nullptr;
}

void Field::KillAnimal(Animal* animal) {
	std::pair<int, int> pos = m_animal_list[animal];
	KillAnimal(pos.first, pos.second);
}

void Field::UpdatePosition(Animal* animal, int x, int y) {
	std::pair<int, int> old_pos = m_animal_list[animal];
	m_animals[old_pos.first][old_pos.second] = nullptr;
	m_animal_list[animal] = { x,y };
	m_animals[x][y] = animal;
}

