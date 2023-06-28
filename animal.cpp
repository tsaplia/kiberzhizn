#include "animal.h"
#include "field.h"

Animal::Animal(int x, int y, Field* parent) {
	InitEmpty(x, y, parent);

	m_color = QColor::fromHsl(rand() % 360, 255, 70 + rand() % 156);
	m_brain = new NetworkOfNodes();
}

Animal::Animal(int x, int y, Animal* animal) {
	InitEmpty(x, y, animal->m_parent);

	m_brain = new NetworkOfNodes(animal->m_brain);
	m_color = animal->m_color;
	m_direction = animal->m_direction;
}

Animal::Animal(int x, int y, Field* parent, NetworkOfNodes* brain, QColor color, AnimalDirections direction) {
	InitEmpty(x, y, parent);

	m_color = color;
	m_brain = brain;
	m_direction = direction;
}

void Animal::InitEmpty(int x, int y, Field* parent) {
	m_x = x;
	m_y = y;
	m_parent = parent;
	m_direction = AnimalDirections(rand() % 4);
	m_energy = Config::GetDefaultEnergy();
	m_attacks_cnt = m_synthesis_cnt = m_age = 0;
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
	return (m_parent->IsInside(x, y) ? std::make_pair(x, y) : NOT_CORD);
}

bool Animal::CanMove() {
	std::pair<int, int> look = LooksAt();
	return look != NOT_CORD && !m_parent->GetAnimal(look.first, look.second);
}

void Animal::Move() {
	std::pair<int, int> look = LooksAt();
	m_x = look.first, m_y = look.second;
	m_parent->UpdatePosition(this, m_x, m_y);
}

bool Animal::CanSynthesize() {
	return Config::GetPhotosynthesis() && m_parent->GetSurface(m_x, m_y) == SurfaceTypes::earth && m_energy <= Config::GetMaxEnergy();
}

void Animal::Photosynthesis() {
	m_energy += Config::GetPhotosynthesisEnergy();
	m_synthesis_cnt++;
}

bool Animal::CanAttack() {
	std::pair<int, int> look = LooksAt();
	return Config::GetKill() && look != NOT_CORD && m_parent->GetAnimal(look.first, look.second) && m_energy <= Config::GetMaxEnergy();
}

void Animal::Attack() {
	std::pair<int, int> look = LooksAt();
	if (Config::GetAlternative()) {
		m_energy += m_parent->GetAnimal(look.first, look.second)->m_energy;
	}
	else {
		m_energy += Config::GetKillEnergy();
	}
	m_parent->KillAnimal(look.first, look.second);
	m_attacks_cnt++;
}

bool Animal::CanReproduce() {
    std::pair<int, int> look = LooksAt();
    return look != NOT_CORD && !m_parent->GetAnimal(look.first, look.second) &&
        (m_energy > Config::GetReproductionEnergy() || (Config::GetAlternative() && m_energy > 1));
}

void Animal::Reproduction() {
	m_reproduction_cnt++;
	std::pair<int, int> look = LooksAt();
	m_parent->AddAnimal(look.first, look.second, Animal::Mutation(this));
	if (Config::GetAlternative()) {
		m_parent->GetAnimal(look.first, look.second)->m_energy = m_energy / 2;
		m_energy /= 2;
	}
	else {
		m_energy -= Config::GetReproductionEnergy();
	}
}

void Animal::Motion() {
	std::vector<double> input = GetBrainInput();
	std::vector<double> output = m_brain->Calculations(input);

	if (!CanMove()) output[0] = -INFINITY;
	if (!CanAttack()) output[1] = -INFINITY;
	if (!CanSynthesize()) output[2] = -INFINITY;
	if (!CanReproduce()) output[3] = -INFINITY;

	int res_ind = std::max_element(output.begin(), output.begin() + 4) - output.begin();
	if (output[res_ind] > 0) {  //optional != -INFINITY
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

	if (output[4] > Config::ROTATION_ACTIVATION) m_direction = AnimalDirections((static_cast<int>(m_direction) + 1) % 4);
	else if (output[4] < -Config::ROTATION_ACTIVATION) m_direction = AnimalDirections((static_cast<int>(m_direction) + 3) % 4);
	m_energy--;
	m_age++;
	if (m_energy < 0 || (Config::GetDeath() && rand() % (std::max(Config::MAX_AGE - m_age, 1) * Config::GetDeathProb()) == 0)) {
		m_parent->KillAnimal(m_x, m_y);
	}
}

std::vector<double> Animal::GetBrainInput() {
	std::vector<double> input(5, 0);
	input[0] = std::min(1.0, (double)m_energy / Config::GetMaxEnergy());

	std::pair<int, int> look = LooksAt();
	if (!m_parent->IsInside(look.first, look.second)) {
		input[1] = 0;
	}
	else if (m_parent->GetAnimal(look.first, look.second)) {
		input[1] = 1;

		QColor color = m_parent->GetAnimal(look.first, look.second)->m_color;
		input[2] = m_color.lightness() == color.lightness() ? 1 - std::abs(m_color.hslHue() - color.hslHue()) / (double)360 : -1;
	}
	else {
		input[1] = -1;
	}

	input[3] = (double)m_y / m_parent->Height();

	return input;
}

QColor Animal::GetLifeColor() {
	QColor color = QColor(255, 255, 0);
	if (m_synthesis_cnt / 2 > m_attacks_cnt) {
		color.setRed(std::max(0, 255 - Config::COLORS_IN_MOUTION * (m_synthesis_cnt / 2 - m_attacks_cnt)));
	}
	else {
		color.setGreen(std::max(0, 255 - Config::COLORS_IN_MOUTION * (m_attacks_cnt - m_synthesis_cnt / 2)));
	}
	return color;
}

QColor Animal::GetFamilyColor() {
	return this->m_color;
}

QColor Animal::GetEnergyColor() {
	return QColor::fromHsl(260, 255, 255 - std::min(m_energy, Config::GetMaxEnergy()) * 255 / Config::GetMaxEnergy());
}

QColor Animal::GetAgeColor() {
	return QColor::fromHsl(33, 255, 255 - std::min(m_age, Config::MAX_AGE) * 255 / Config::MAX_AGE);
}

AnimalStats Animal::GetStats() {
	return AnimalStats {m_energy, m_age, m_attacks_cnt, m_synthesis_cnt, m_reproduction_cnt, m_color, m_x, m_y};
}

Animal::~Animal() {
	delete m_brain;
}

Animal* Animal::Mutation(Animal* animal) {
	NetworkOfNodes* brain = new NetworkOfNodes(animal->m_brain);
	QColor color = animal->m_color;

	if (Config::GetMutation() && rand() % Config::MUTATION_PROBABILITY == 0) {
		int mutations_cnt = animal->m_brain->Mutations();
		color.setHsl((color.hue() + mutations_cnt) % 360, color.saturation(), color.lightness());
	}

	std::pair<int, int> pos = animal->LooksAt();
	return new Animal(pos.first, pos.second, animal->m_parent, brain, color, animal->m_direction);
}
