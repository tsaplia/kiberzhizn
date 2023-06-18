#include "interface.h"

Interface::Interface(PainterArea* painter) {
	m_painter = painter;
	
	m_start_or_stop = new QPushButton("Start");
	m_clear = new QPushButton("Clear");
	m_spawn = new QPushButton("Spawn");

	m_migration_check = new QCheckBox("Migration");
	m_death_check = new QCheckBox("Death");
	
	m_timer_interval_label = new QLabel("Action interval: ");
	m_default_energy_label = new QLabel("Defaul energy: ");
	m_photosynthesis_energy_label = new QLabel("Photosynthesis energy: ");
	m_kill_energy_label = new QLabel("Kill energy: ");
	m_reproduction_energy_label = new QLabel("Reproduction energy: ");
	m_max_energy_label = new QLabel("Max energy: ");
	m_migration_in_act_label = new QLabel("Every actions: ");
	m_migration_prob_label = new QLabel("Chance 1 in: ");
	m_death_prob_label = new QLabel("Chance 1 in: ");
	m_erase_radius_label = new QLabel("Erase radius: ");

	m_timer_interval_edit = new QLineEdit("500");
	m_default_energy_edit = new QLineEdit("4");
	m_photosynthesis_energy_edit = new QLineEdit("4");
	m_kill_energy_edit = new QLineEdit("10");
	m_reproduction_energy_edit = new QLineEdit("10");
	m_max_energy_edit = new QLineEdit("60");
	m_migration_in_act_edit = new QLineEdit("5");
	m_migration_prob_edit = new QLineEdit("20");
	m_death_prob_edit = new QLineEdit("100");
	m_erase_radius_edit = new QLineEdit("10");

	m_color_combo = new QComboBox();
	
	m_group_values = new QGroupBox("Values");
	m_group_features = new QGroupBox("Features");

	m_vbox_layout = new QVBoxLayout();
	m_grid_values = new QGridLayout();
	m_grid_features = new QGridLayout();

	Settings();
	Connections();
}

Interface::~Interface() {

}

void Interface::Settings() {
	m_start_or_stop->setFixedWidth(150);
	m_spawn->setFixedWidth(150);
	m_clear->setFixedWidth(150);
	m_color_combo->setFixedWidth(150);

	m_color_combo->addItem("Family");
	m_color_combo->addItem("Life");
	m_color_combo->addItem("Energy");
	m_color_combo->addItem("Age");

	m_vbox_layout->addWidget(m_start_or_stop);
	m_vbox_layout->addWidget(m_spawn);
	m_vbox_layout->addWidget(m_clear);
	m_vbox_layout->addWidget(m_color_combo);
	m_vbox_layout->addWidget(m_group_values);
	m_vbox_layout->addWidget(m_group_features);
	m_vbox_layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	m_grid_values->addWidget(m_timer_interval_label, 0, 0);
	m_grid_values->addWidget(m_timer_interval_edit, 0, 1);
	m_grid_values->addWidget(m_default_energy_label, 1, 0);
	m_grid_values->addWidget(m_default_energy_edit, 1, 1);
	m_grid_values->addWidget(m_photosynthesis_energy_label, 2, 0);
	m_grid_values->addWidget(m_photosynthesis_energy_edit, 2, 1);
	m_grid_values->addWidget(m_kill_energy_label, 3, 0);
	m_grid_values->addWidget(m_kill_energy_edit, 3, 1);
	m_grid_values->addWidget(m_reproduction_energy_label, 4, 0);
	m_grid_values->addWidget(m_reproduction_energy_edit, 4, 1);
	m_grid_values->addWidget(m_max_energy_label, 5, 0);
	m_grid_values->addWidget(m_max_energy_edit, 5, 1);

	m_group_values->setLayout(m_grid_values);
	m_group_values->setCheckable(true);
	m_group_values->setChecked(false);
	GroupValuesHide();

	m_grid_features->addWidget(m_migration_check, 0, 0);
	m_grid_features->addWidget(m_migration_in_act_label, 1, 0);
	m_grid_features->addWidget(m_migration_in_act_edit, 1, 1);
	m_grid_features->addWidget(m_migration_prob_label, 2, 0);
	m_grid_features->addWidget(m_migration_prob_edit, 2, 1);
	m_grid_features->addWidget(m_death_check, 3, 0);
	m_grid_features->addWidget(m_death_prob_label, 4, 0);
	m_grid_features->addWidget(m_death_prob_edit, 4, 1);
	m_grid_features->addWidget(m_erase_radius_label, 5, 0);
	m_grid_features->addWidget(m_erase_radius_edit, 5, 1);

	m_group_features->setLayout(m_grid_features);
	m_group_features->setCheckable(true);
	m_group_features->setChecked(false);


	setLayout(m_vbox_layout);
	setMaximumWidth(250);

	m_painter->SetTimerInterval(TIMER_INTERVAL);
}

void Interface::Connections() {
	connect(m_start_or_stop, &QPushButton::clicked, this, &Interface::StartOrStop);
	connect(m_spawn, &QPushButton::clicked, this, &Interface::SpawnAnimal);
	connect(m_clear, &QPushButton::clicked, this, &Interface::ClearField);
	connect(m_color_combo, &QComboBox::currentTextChanged, this, &Interface::AnimalColor);
	
	connect(m_group_values, &QGroupBox::clicked, this, &Interface::GroupValuesVisible);
	connect(m_timer_interval_edit, &QLineEdit::textChanged, this, &Interface::ChangeTimerInterval);
	connect(m_default_energy_edit, &QLineEdit::textChanged, this, &Interface::ChangeDefaultEnergy);
	connect(m_photosynthesis_energy_edit, &QLineEdit::textChanged, this, &Interface::ChangePhotosynthesisEnergy);
	connect(m_kill_energy_edit, &QLineEdit::textChanged, this, &Interface::ChangeKillEnergy);
	connect(m_reproduction_energy_edit, &QLineEdit::textChanged, this, &Interface::ChangeReproductionEnergy);
	connect(m_max_energy_edit, &QLineEdit::textChanged, this, &Interface::ChangeMaxEnergy);


}

void Interface::StartOrStop() {
	if (m_active_status) Stop();
	else Start();

	return;
}

void Interface::Start() {
	m_start_or_stop->setText("Stop");

	m_timer_interval_edit->setEnabled(false);
	m_default_energy_edit->setEnabled(false);
	m_photosynthesis_energy_edit->setEnabled(false);
	m_kill_energy_edit->setEnabled(false);
	m_reproduction_energy_edit->setEnabled(false);
	m_max_energy_edit->setEnabled(false);
	
	m_painter->Start();
	m_active_status ^= 1;
}

void Interface::Stop() {
	m_start_or_stop->setText("Start");
	
	m_timer_interval_edit->setEnabled(true);
	m_default_energy_edit->setEnabled(true);
	m_photosynthesis_energy_edit->setEnabled(true);
	m_kill_energy_edit->setEnabled(true);
	m_reproduction_energy_edit->setEnabled(true);
	m_max_energy_edit->setEnabled(true);

	m_painter->Pause();
	m_active_status ^= 1;
}

void Interface::SpawnAnimal() {
	ClearField();
	m_painter->Spawn();
}

void Interface::ClearField() {
	m_painter->Clear();
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

void Interface::GroupValuesVisible() {
	if (m_group_values_visible) GroupValuesHide();
	else GroupValuesShow();
	m_group_values_visible ^= 1;
}

void Interface::GroupValuesHide() {
	m_timer_interval_label->hide();
	m_timer_interval_edit->hide();
	m_default_energy_label->hide();
	m_default_energy_edit->hide();
	m_photosynthesis_energy_label->hide();
	m_photosynthesis_energy_edit->hide();
	m_kill_energy_label->hide();
	m_kill_energy_edit->hide();
	m_reproduction_energy_label->hide();
	m_reproduction_energy_edit->hide();
	m_max_energy_label->hide();
	m_max_energy_edit->hide();
}

void Interface::GroupValuesShow() {
	m_timer_interval_label->show();
	m_timer_interval_edit->show();
	m_default_energy_label->show();
	m_default_energy_edit->show();
	m_photosynthesis_energy_label->show();
	m_photosynthesis_energy_edit->show();
	m_kill_energy_label->show();
	m_kill_energy_edit->show();
	m_reproduction_energy_label->show();
	m_reproduction_energy_edit->show();
	m_max_energy_label->show();
	m_max_energy_edit->show();
}

void Interface::ChangeTimerInterval() {
	int timer_interval = m_timer_interval_edit->text().toInt();
	m_painter->SetTimerInterval(timer_interval);
}

void Interface::ChangeDefaultEnergy() {
	Config::SetDefaultEnergy(m_default_energy_edit->text().toInt());
}

void Interface::ChangePhotosynthesisEnergy() {
	Config::SetPhotosynthesisEnergy(m_photosynthesis_energy_edit->text().toInt());
}

void Interface::ChangeKillEnergy() {
	Config::SetKillEnergy(m_kill_energy_edit->text().toInt());
}

void Interface::ChangeReproductionEnergy() {
	Config::SetReproductionEnergy(m_reproduction_energy_edit->text().toInt());
}

void Interface::ChangeMaxEnergy() {
	Config::SetMaxEnergy(m_max_energy_edit->text().toInt());
}