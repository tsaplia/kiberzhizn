#include "interface.h"

Interface::Interface(PainterArea* painter) {
	m_painter = painter;
	m_start_or_stop = new QPushButton("Start");
	m_timer_interval_edit = new QLineEdit("500");
	m_color_combo = new QComboBox();
	m_vbox_layout = new QVBoxLayout();

	Settings();
	Connections();

}

Interface::~Interface() {

}

void Interface::Settings() {
	m_color_combo->addItem("Family");
	m_color_combo->addItem("Life");
	m_color_combo->addItem("Energy");

	m_vbox_layout->addWidget(m_start_or_stop);
	m_vbox_layout->addWidget(m_timer_interval_edit);
	m_vbox_layout->addWidget(m_color_combo);


	m_vbox_layout->setAlignment(Qt::AlignRight | Qt::AlignTop);
	setLayout(m_vbox_layout);
	setMaximumWidth(100);

	Node::SetWeightMulti(WEIGHT_MULTI);


	return;
}

void Interface::Connections() {
	connect(m_start_or_stop, &QPushButton::clicked, this, &Interface::StartOrStop);
	connect(m_timer_interval_edit, &QLineEdit::textChanged, this, &Interface::ChangeTimerInterval);
	connect(m_color_combo, &QComboBox::currentTextChanged, this, &Interface::AnimalColor);
}

void Interface::StartOrStop() {
	if (m_active_status) Stop();
	else Start();

	return;
}

void Interface::Start() {
	m_start_or_stop->setText("Stop");
	m_timer_interval_edit->setEnabled(false);
	m_painter->Start();
	m_active_status ^= 1;
}

void Interface::Stop() {
	m_start_or_stop->setText("Start");
	m_timer_interval_edit->setEnabled(true);
	m_painter->Pause();
	m_active_status ^= 1;
}

void Interface::ChangeTimerInterval() {
	int timer_interval = m_timer_interval_edit->text().toInt();
	m_painter->SetTimerInterval(timer_interval);
}

void Interface::AnimalColor() {
	AnimalColors animal_color;
	QString s = m_color_combo->currentText();
	if (s == "Family") animal_color = AnimalColors::family;
	else if (s == "Life") animal_color = AnimalColors::life;
	else if (s == "Energy") animal_color = AnimalColors::energy;
	m_painter->SetAnimalColor(animal_color);
}