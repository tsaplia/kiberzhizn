#include "animal.h"
#include "field.h"

const int DEFAULT_ENERGY = 8;
const int PHOTOSYNTHESIS_ENERGY = 4;
const int KILL_ENERGY = 8;
const int REPRODUCTION_ENERGY = 8;

const std::pair<int, int> LOOKS_AT_BORDER = std::make_pair(-1,-1);


Animal::Animal(int x, int y, Field* parent) {
	InitEmpty(x, y, parent);

	srand(time(0));
	m_color = QColor(rand() % 255, rand() % 255, rand() % 255);
	m_brain = new NetworkOfNodes();
}

Animal::Animal(int x, int y, Field* parent, NetworkOfNodes* brain, QColor color) {
	InitEmpty(x, y, parent);

	m_color = color;
	m_brain = brain;
}

void Animal::InitEmpty(int x, int y, Field* parent) {
	m_x = x;
	m_y = y;
	m_parent = parent;
	m_direction = AnimalDirections::up;
	m_energy = DEFAULT_ENERGY;
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
	m_parent->AddAnimal(look.first, look.second, Animal::Mutation(this));
	m_energy -= REPRODUCTION_ENERGY;
}

void Animal::Motion() {
	std::vector<double> input = GetBrainInput();
	std::vector<double> output = m_brain->Calculations(input);

	if (!CanMove()) output[0] = -INFINITY;
	if(!CanAttack()) output[1] = -INFINITY;
	if (!CanSynthesize()) output[2] = -INFINITY;
	if (!CanReproduce()) output[3] = -INFINITY;

	int res_ind = std::max_element(output.begin(), output.begin()+4) - output.begin();
	if (output[res_ind] != -INFINITY) {
		switch (res_ind)
		{
		case 0:
			Move();
			break;
		case 1:
			Attack();
			break;
		case 2:
			Photosynthesis();
			break;
		case 3:
			Reproduction();
			break;
		}
	}
	
	if (input[4] > 0.4) m_direction = AnimalDirections((m_direction + 1) % 4);
	else if (input[4] < -0.4) m_direction = AnimalDirections((4 + m_direction - 1) % 4);
}

std::vector<double> Animal::GetBrainInput() {
	std::vector<double> input(5, 0);
	input[0] = std::min(1.0, (double)m_energy / 100);

	std::pair<int, int> look = LooksAt();
	if (!m_parent->IsInside(look.first, look.second)) {
		input[1] = 0;
	}
	else if (m_parent->GetAnimal(look.first, look.second)) {
		input[1] = 1;

		QColor color =  m_parent->GetAnimal(look.first, look.second)->m_color;
		int int_color = (color.red() << 16) | (color.green() << 8) | color.blue();
		input[2] = (double)int_color / (1 << 24);
	}
	else {
		input[1] = -1;
	}

	input[3] = (double)m_y / m_parent->Height();
	input[4] = (double)m_x / m_parent->Width();

	return input;
}

Animal::~Animal() {
	delete m_brain;
}

Animal* Animal::Mutation(Animal* animal) {
	NetworkOfNodes* brain = new NetworkOfNodes(animal->m_brain); 
	QColor color = animal->m_color;

	int mutations_cnt = animal->m_brain->Mutations();
	color.setHsl((color.hue() + mutations_cnt) % 360, color.saturation(), color.lightness());

	std::pair<int, int> pos = animal->LooksAt();
	return new Animal(pos.first, pos.second, animal->m_parent, brain, color);
}
