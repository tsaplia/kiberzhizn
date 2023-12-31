#include "painter.h"

PainterArea::PainterArea(Statistics* stats) {
	m_stats = stats;
	m_field = new Field(Config::COLS, Config::ROWS);
	m_timer = new QTimer();
	m_timer->setInterval(Config::DEFAULT_INTERVAL);
	connect(m_timer, &QTimer::timeout, this, &PainterArea::TimerTick);
	m_state = States::start;
	update();

	m_selected_cord = NOT_CORD;
	m_flash_timer = new QTimer();
	m_flash_timer->setInterval(Config::FLASH_INTERVAL);
	connect(m_flash_timer, &QTimer::timeout, this, &PainterArea::FlasTick);
}

PainterArea::~PainterArea() {
	delete m_field;
}

void PainterArea::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	QPen pen = QPen(Qt::white);
	pen.setWidth(1);
	painter.setPen(pen);

	painter.setBrush(earth_color);
	painter.drawRect(0, 0, m_width, m_field->GetWaterLavel() * m_ceil_height);
	painter.setBrush(water_color);
	painter.drawRect(0, m_field->GetWaterLavel() * m_ceil_height, m_width, m_height - m_field->GetWaterLavel() * m_ceil_height);

	for (int x = 0; x < Config::COLS; x++) {
		for (int y = 0; y < Config::ROWS; y++) {
			Animal* animal = m_field->GetAnimal(x, y);
			if (!animal) continue;

			else painter.setBrush(GetAnimalColor(animal));
			painter.drawRect(x * m_ceil_width, y * m_ceil_height, m_ceil_width, m_ceil_height);
		}
	}
	m_stats->SetFieldStats(m_field->GetStats());

	if (m_selected_cord == NOT_CORD || !m_field->GetAnimal(m_selected_cord.first, m_selected_cord.second)) return;
	int x = m_selected_cord.first, y = m_selected_cord.second;
	Animal* selected_animal = m_field->GetAnimal(m_selected_cord.first, m_selected_cord.second);

	painter.setPen(Qt::white);
	if (m_selectd_visible) painter.setBrush(GetAnimalColor(selected_animal));
	else painter.setBrush(Qt::black);
	painter.drawRect(x * m_ceil_width, y * m_ceil_height, m_ceil_width, m_ceil_height);

	m_selectd_visible = !m_selectd_visible;
}

QColor PainterArea::GetAnimalColor(Animal* animal) {
	if (m_animal_color == AnimalColors::family) return animal->GetFamilyColor();
	if (m_animal_color == AnimalColors::life) return animal->GetLifeColor();
	if (m_animal_color == AnimalColors::energy) return animal->GetEnergyColor();
	return animal->GetAgeColor();
}

void PainterArea::resizeEvent(QResizeEvent* event) {
	m_height = this->height();
	this->setFixedWidth(m_height * Config::COLS / Config::ROWS);
	m_width = this->width();
	m_ceil_width = (double)m_width / Config::COLS;
	m_ceil_height = (double)m_height / Config::ROWS;
}

void  PainterArea::mousePressEvent(QMouseEvent* event) {
	int x = event->pos().x() / m_ceil_width;
	int y = event->pos().y() / m_ceil_height;

	if (m_state == States::select_animal) {
		m_selected_cord = std::make_pair(x, y);
		if (AnimalSelected()) {
			m_stats->SetAnimalStats(m_field->GetAnimal(x,y)->GetStats());
		}
		else {
			m_stats->HideAnimalStats();
		}
		return;
	}

	if (event->button() == Qt::LeftButton) {
		if (m_field->GetAnimal(x, y)) m_field->KillAnimal(x, y);
		else {
			if (m_current_animal == RANDOM_ANIMAL) {
				m_field->AddAnimal(x, y);
			}
			else {
				Animal* new_animal = new Animal(x, y, m_loaded_animals[m_current_animal]);
				m_field->AddAnimal(x, y, new_animal);
			}
		}
	}
	else {
		ClearArea(x, y, Config::GetEracerRadius());
		m_right_button_pressed = true;
	}
	update();
}

void PainterArea::mouseMoveEvent(QMouseEvent* event) {
	if (m_right_button_pressed) {
		int x = event->pos().x() / m_ceil_width;
		int y = event->pos().y() / m_ceil_height;
		ClearArea(x, y, Config::GetEracerRadius());
	}
}

void PainterArea::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::RightButton) {
		m_right_button_pressed = false;
		update();
	}
}

void PainterArea::ClearArea(int x, int y, int r) {
	for (int i = std::max(x - r, 0); i <= std::min(x + r, Config::COLS - 1); i++) {
		for (int j = std::max(y - r, 0); j <= std::min(y + r, Config::ROWS - 1); j++) {
			m_field->KillAnimal(i, j);
		}
	}
}

void PainterArea::Start() {
	if (m_state != States::paused && m_state != States::start) return;
	m_timer->start();
	m_state = States::working;
}

void PainterArea::Pause() {
	if (m_state != States::working) return;
	m_timer->stop();
	m_state = States::paused;
}

void PainterArea::TimerTick() {
	m_timer->stop();

	m_field->Moution();
	if (Config::GetMigration() && rand() % Config::GetMigrationProb() == 0) {
		m_field->RandGen(Config::ROWS * Config::COLS - m_field->GetAnimalsCnt());
	}
	update();

	if (m_state == States::working) m_timer->start();
}

void PainterArea::SkipMoution(int steps) {
	if (m_state == States::working) Pause();
	if (m_state != States::paused && m_state != States::start) return;

	while (steps--) {
		m_field->Moution();
		if (Config::GetMigration() && rand() % Config::GetMigrationProb() == 0) {
			m_field->RandGen(Config::ROWS * Config::COLS - m_field->GetAnimalsCnt());
		}
	}
}

void PainterArea::SetTimerInterval(int value) {
	if (m_state == States::paused || m_state == States::start) {
		m_timer->setInterval(value);
	}
}

void PainterArea::SetAnimal(QString animal_name) {
	if (animal_name == RANDOM_ANIMAL || m_loaded_animals.find(animal_name) != m_loaded_animals.end()) {
		m_current_animal = animal_name;
	}
}

void PainterArea::SetAnimalColor(AnimalColors color) {
	m_animal_color = color;
	update();
}

void PainterArea::Clear() {
	if (m_state == States::working || m_state == States::paused || m_state == States::start) {
		m_field->Clear();
		m_state = States::start;
		update();
	}
}

void PainterArea::Spawn() {
	if (m_state == States::start) {
		m_field->RandGen(Config::GetRandomProb());
		update();
	}
}

void PainterArea::SelectAnimal() {
	if (m_state == States::working) Pause();
	if (m_state != States::paused && m_state != States::start) return;

	m_state = States::select_animal;
	m_flash_timer->start();
}

bool PainterArea::AnimalSelected() {
	return m_selected_cord != NOT_CORD && m_field->GetAnimal(m_selected_cord.first, m_selected_cord.second);
}

void PainterArea::FlasTick() {
	update();
}

bool PainterArea::SaveAnimal(QString filename) {
	if (m_state != States::select_animal || !AnimalSelected()) return false;

	Animal* animal = m_field->GetAnimal(m_selected_cord.first, m_selected_cord.second);
	bool animal_bool = animal->Save(filename.toStdString());
	m_selected_cord = NOT_CORD;
	m_stats->HideAnimalStats();
	return true;
}

void PainterArea::RemoveSelection() {
	if (m_state != States::select_animal) return;
	m_selectd_visible = false;
	m_state = States::paused;
	m_flash_timer->stop();
	m_selected_cord = NOT_CORD;
	m_stats->HideAnimalStats();
	update();
}

bool PainterArea::AnimalFromFile(QString filename) {
	Animal* animal = Animal::FromFile(0, 0, m_field, filename.toStdString());
	if (animal) {
		QString animal_name = filename.section("/", -1, -1).section(".", 0, 0);
		m_loaded_animals[animal_name] = animal;
	}
	return animal != nullptr;
}
