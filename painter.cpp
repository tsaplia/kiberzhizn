#include "painter.h"

PainterArea::PainterArea() {
	m_field = new Field(Config::COLS, Config::ROWS);
	m_timer = new QTimer();
	m_timer->setInterval(Config::DEFAULT_INTERVAL);
	connect(m_timer, &QTimer::timeout, this, &PainterArea::TimerTick);
	m_state = States::start;
	update();
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

			if (m_animal_color == AnimalColors::family) painter.setBrush(animal->GetFamilyColor());
			else if (m_animal_color == AnimalColors::life) painter.setBrush(animal->GetLifeColor());
			else if (m_animal_color == AnimalColors::energy) painter.setBrush(animal->GetEnergyColor());
			else painter.setBrush(animal->GetAgeColor());

			painter.drawRect(x * m_ceil_width, y * m_ceil_height, m_ceil_width, m_ceil_height);
		}
	}
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

	if (event->button() == Qt::LeftButton) {
		if (m_field->GetAnimal(x, y)) m_field->KillAnimal(x, y);
		else m_field->AddAnimal(x, y);
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
	m_timer->start();
	m_state = States::working;
}

void PainterArea::Pause() {
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

void PainterArea::SetTimerInterval(int value) {
	if (m_state == States::paused || m_state == States::start) {
		m_timer->setInterval(value);
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