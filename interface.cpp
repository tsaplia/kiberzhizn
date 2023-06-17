#include "interface.h"

Interface::Interface(PainterArea* painter) {
	m_painter = painter;
	
	m_start_or_stop = new QPushButton("Start");
	m_clear = new QPushButton("Clear");
	
	m_default_energy_label = new QLabel("Defaul energy: ");
	m_max_energy_label = new QLabel("Max energy: ");

	m_timer_interval_edit = new QLineEdit("500");
	m_default_energy_edit = new QLineEdit("4");
	m_max_energy_edit = new QLineEdit("25");

	m_color_combo = new QComboBox();
	
	m_group_values = new QGroupBox("Values");

	m_vbox_layout = new QVBoxLayout();
	m_grid_values = new QGridLayout();

	Settings();
	Connections();

}

Interface::~Interface() {

}

void Interface::Settings() {
	m_color_combo->addItem("Family");
	m_color_combo->addItem("Life");
	m_color_combo->addItem("Energy");
	m_color_combo->addItem("Age");

	m_vbox_layout->addWidget(m_start_or_stop);
	m_vbox_layout->addWidget(m_timer_interval_edit);
	m_vbox_layout->addWidget(m_clear);
	m_vbox_layout->addWidget(m_color_combo);
	m_vbox_layout->addWidget(m_group_values);
	m_vbox_layout->setAlignment(Qt::AlignRight | Qt::AlignTop);

	m_grid_values->addWidget(m_default_energy_label, 0, 0);
	m_grid_values->addWidget(m_default_energy_edit, 0, 1);
	m_grid_values->addWidget(m_max_energy_label, 1, 0);
	m_grid_values->addWidget(m_max_energy_edit, 1, 1);

	m_group_values->setLayout(m_grid_values);
	m_group_values->setCheckable(true);
	m_group_values->setChecked(false);
	GroupValuesHide();

	setLayout(m_vbox_layout);
	setMaximumWidth(200);

	Node::SetWeightMulti(WEIGHT_MULTI);
	m_painter->SetTimerInterval(TIMER_INTERVAL);
}

void Interface::Connections() {
	connect(m_start_or_stop, &QPushButton::clicked, this, &Interface::StartOrStop);
	connect(m_clear, &QPushButton::clicked, this, &Interface::ClearField);
	connect(m_timer_interval_edit, &QLineEdit::textChanged, this, &Interface::ChangeTimerInterval);
	connect(m_color_combo, &QComboBox::currentTextChanged, this, &Interface::AnimalColor);
	connect(m_group_values, &QGroupBox::clicked, this, &Interface::GroupValuesVisible);
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
	else animal_color = AnimalColors::age;
	m_painter->SetAnimalColor(animal_color);
}

void Interface::ClearField() {
	m_painter->Clear();
}

void Interface::GroupValuesVisible() {
	if (m_group_values_visible) GroupValuesHide();
	else GroupValuesShow();
	m_group_values_visible ^= 1;
}

void Interface::GroupValuesHide() {
	m_default_energy_label->setVisible(false);
	m_default_energy_edit->setVisible(false);
	m_max_energy_label->setVisible(false);
	m_max_energy_edit->setVisible(false);
}

void Interface::GroupValuesShow() {
	m_default_energy_label->setVisible(true);
	m_default_energy_edit->setVisible(true);
	m_max_energy_label->setVisible(true);
	m_max_energy_edit->setVisible(true);
}