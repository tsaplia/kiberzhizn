#include "painter.h"

PainterArea::PainterArea() {
	m_field = new Field(m_col, m_row);
	m_field->RandGen(10);
	m_timer = new QTimer();
	m_timer->setInterval(m_timer_interval);
	connect(m_timer, &QTimer::timeout, this, &PainterArea::TimerTick);
	m_state = States::paused;
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
	painter.drawRect(0, (int)(m_row * 0.75) * m_ceil_height, m_width, m_height - m_field->GetWaterLavel() * m_ceil_height);

	for (int x = 0; x < m_col; x++) {
		for (int y = 0; y < m_row; y++) {
			Animal* animal = m_field->GetAnimal(x, y);
			if (!animal) continue;

			if(m_animal_color == AnimalColors::family) painter.setBrush(animal->GetFamilyColor());
			else if (m_animal_color == AnimalColors::life) painter.setBrush(animal->GetLifeColor());
			else if (m_animal_color == AnimalColors::energy) painter.setBrush(animal->GetEnergyColor());
			else painter.setBrush(animal->GetAgeColor());

			painter.drawRect(x * m_ceil_width, y * m_ceil_height, m_ceil_width, m_ceil_height);
		}
	}
}

void PainterArea::resizeEvent(QResizeEvent* event) {
	m_height = this->height();
	this->setFixedWidth(m_height*m_col/m_row);
	m_width = this->width();
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
	for (int i = 0; i < m_moution_update; i++) {
		m_field->Moution();
	}
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