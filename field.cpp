#include "field.h"
#include "statistics.h"

Field::Field(int width, int height) {
	m_height = height;
	m_width = width;
	m_water_level = static_cast<int>(height * Config::WATER_LAVEL);
	m_animals.resize(width, std::vector<Animal*>(height));
}

int Field::Width() {
	return m_width;
}

int Field::Height() {
	return m_height;
}

void Field::AddAnimal(int x, int y) {
	if (IsInside(x, y)) {
		AddAnimal(x, y, new Animal(x, y, this));
	}
}

void Field::AddAnimal(int x, int y, Animal* animal) {
	if (!IsInside(x, y)) return;
	if (this->GetAnimal(x, y)) this->KillAnimal(x, y);

	m_animals_cnt++;
	m_born_cnt++;
	m_animals[x][y] = animal;
	m_animal_list[m_animals[x][y]] = { x,y };
	m_processed.insert(animal);
}

Animal* Field::GetAnimal(int x, int y) {
	return (IsInside(x, y) ? m_animals[x][y] : nullptr);
}

void Field::KillAnimal(int x, int y) {
	if(!IsInside(x, y) || !m_animals[x][y]) return;

	m_animals_cnt--;
	m_kills_cnt++;
	m_animal_list.erase(m_animals[x][y]);
	delete m_animals[x][y];
	m_animals[x][y] = nullptr;
}

void Field::KillAnimal(Animal* animal) {
	std::pair<int, int> pos = m_animal_list[animal];
	KillAnimal(pos.first, pos.second);
}

void Field::UpdatePosition(Animal* animal, int x, int y) {
	if (!IsInside(x, y) || m_animals[x][y]) return;

	std::pair<int, int> old_pos = m_animal_list[animal];
	m_animals[old_pos.first][old_pos.second] = nullptr;
	m_animal_list[animal] = { x,y };
	m_animals[x][y] = animal;
	m_processed.insert(animal);
}

SurfaceTypes Field::GetSurface(int x, int y) {
	return (y >= m_water_level ? SurfaceTypes::water : SurfaceTypes::earth);
}

int Field::GetAnimalsCnt() {
	return m_animals_cnt;
}

FieldStats Field::GetStats() {
	return FieldStats { m_animals_cnt, m_kills_cnt, m_born_cnt };
}

int Field::GetWaterLavel() {
	return this->m_water_level;
}

bool Field::IsInside(int x, int y) {
	return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

void Field::Moution() {
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			if (m_animals[i][j] != nullptr && !m_processed.contains(m_animals[i][j])) {
				m_animals[i][j]->Motion();
			}
		}
	}

	m_processed.clear();
}

void Field::Clear() {
	m_born_cnt = m_kills_cnt = 0;
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			if (m_animals[i][j]) KillAnimal(i, j);
		}
	}
}

void Field::RandGen(int mod) {
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			if (m_animals[i][j]) continue;
			int t = rand() % mod;
			if (rand() % mod == 0) {
				AddAnimal(i, j);
			}
		}
	}
}

Field::~Field() {
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			delete m_animals[i][j];
		}
		m_animals[i].clear();
		m_animals[i].shrink_to_fit();
	}
	m_animals.clear();
	m_animals.shrink_to_fit();
	m_animal_list.clear();
}



