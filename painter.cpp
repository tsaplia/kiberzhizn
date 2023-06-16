#include "painter.h"

PainterArea::PainterArea() {
	m_field = new Field(m_col, m_row);
	m_timer = new QTimer();
	m_timer->setInterval(m_timer_interval);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(TimerTick()));
	m_state = States::paused;
}

PainterArea::~PainterArea() {
	delete m_field;
}

void PainterArea::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setPen(Qt::white);

	for (int x = 0; x < m_col; x++) {
		for (int y = 0; y < m_row; y++) {
			if (m_field->GetSurface(x, y) == SurfaceTypes::water) {
				painter.setBrush(water_color);
			}
			else {
				painter.setBrush(earth_color);
			}
			painter.drawRect(x * m_ceil_width, y * m_ceil_height, m_ceil_width, m_ceil_height);
		}
	}

	for (int x = 0; x < m_col; x++) {
		for (int y = 0; y < m_row; y++) {
			Animal* animal = m_field->GetAnimal(x, y);
			if (!animal) continue;

			if(m_animal_color == AnimalColors::family) painter.setBrush(animal->GetFamilyColor());
			else if (m_animal_color == AnimalColors::life) painter.setBrush(animal->GetLifeColor());
			else painter.setBrush(animal->GetEnergyColor());

			painter.drawRect(x * m_ceil_width, y * m_ceil_height, m_ceil_width, m_ceil_height);
		}
	}
}

void PainterArea::resizeEvent(QResizeEvent* event) {
	m_width = this->width();
	m_height = this->height();
	m_ceil_width = (double)m_width / m_col;
	m_ceil_height = (double)m_height / m_row;
}

void  PainterArea::mousePressEvent(QMouseEvent* event) {
	int x = event->pos().x() / m_ceil_width;
	int y = event->pos().y() / m_ceil_height;
	if (m_field->GetAnimal(x, y)) m_field->KillAnimal(x, y);
	else m_field->AddAnimal(x, y);
	update();
}

void PainterArea::Start() {
	m_timer->setInterval(m_timer_interval);
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
	update();
	if(m_state == States::working) m_timer->start();
}

void PainterArea::SetTimerInterval(int value) {
	if (m_state == States::paused) {
		m_timer_interval = value;
		m_timer->setInterval(value);
	}
}

void PainterArea::SetAnimalColor(AnimalColors color) {
	m_animal_color = color;
	update();
}