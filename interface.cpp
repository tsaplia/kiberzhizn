#include "interface.h"

Interface::Interface(PainterArea* painter, Statistics* statistics) {
	m_painter = painter;
	m_statistics = statistics;

	// 0 - main
	m_start_or_stop = new QPushButton("Start");
	m_skip = new QPushButton("Skip");
	m_clear = new QPushButton("Clear");
	m_spawn = new QPushButton("Spawn");
	m_save_mode = new QPushButton("Save mode");
	m_save = new QPushButton("Save");
	m_open = new QPushButton("Open");

	m_mutation_check = new QCheckBox("Mutation");
	m_photosynthesis_check = new QCheckBox("Photosynthesis");
	m_kill_check = new QCheckBox("Kill");
	m_alternative_check = new QCheckBox("Alternative reprod. and kill");
	m_migration_check = new QCheckBox("Migration");
	m_death_check = new QCheckBox("Death");

	m_skip_progress = new QProgressBar();

	m_skip_label = new QLabel("Skip actions: ");
	// 1 - groupbox values
	m_timer_interval_label = new QLabel("Action interval: ");
	m_default_energy_label = new QLabel("Defaul energy: ");
	m_photosynthesis_energy_label = new QLabel("Photosynthesis energy: ");
	m_kill_energy_label = new QLabel("Kill energy: ");
	m_reproduction_energy_label = new QLabel("Reproduction energy: ");
	m_max_energy_label = new QLabel("Max energy: ");
	m_random_prob_label = new QLabel("Random prob: ");
	m_erase_radius_label = new QLabel("Erase radius: ");
	// 2 - groupbox features
	m_migration_prob_label = new QLabel("Chance 1 in: ");
	m_death_prob_label = new QLabel("Chance 1 in: ");

	m_skip_edit = new QLineEdit("100");
	// 1 - groupbox values
	m_timer_interval_edit = new QLineEdit(QString::number(Config::DEFAULT_INTERVAL));
	m_default_energy_edit = new QLineEdit(QString::number(Config::GetDefaultEnergy()));
	m_photosynthesis_energy_edit = new QLineEdit(QString::number(Config::GetPhotosynthesisEnergy()));
	m_kill_energy_edit = new QLineEdit(QString::number(Config::GetKillEnergy()));
	m_reproduction_energy_edit = new QLineEdit(QString::number(Config::GetReproductionEnergy()));
	m_max_energy_edit = new QLineEdit(QString::number(Config::GetMaxEnergy()));
	m_random_prob_edit = new QLineEdit(QString::number(Config::GetRandomProb()));
	m_erase_radius_edit = new QLineEdit(QString::number(Config::GetEracerRadius()));
	// 2 - groupbox features
	m_migration_prob_edit = new QLineEdit(QString::number(Config::GetMigrationProb()));
	m_death_prob_edit = new QLineEdit(QString::number(Config::GetDeathProb()));

	m_color_combo = new QComboBox();
	m_open_combo = new QComboBox();

	m_group_values = new QGroupBox("Values");
	m_group_features = new QGroupBox("Features");

	m_hbox_layout = new QHBoxLayout();
	m_vbox_layout = new QVBoxLayout();
	m_hbox_skip = new QHBoxLayout();
	m_hbox_save = new QHBoxLayout();
	m_hbox_open = new QHBoxLayout();
	m_grid_values = new QGridLayout();
	m_grid_features = new QGridLayout();

	Settings();
	Connections();
}

Interface::~Interface() {

}

void Interface::Settings() {
	// 0 - main
	m_start_or_stop->setFixedWidth(150);
	m_skip->setFixedWidth(150);
	m_skip_label->setFixedWidth(100);
	m_skip_edit->setFixedWidth(44);
	m_skip_progress->setFixedWidth(150);
	m_spawn->setFixedWidth(150);
	m_clear->setFixedWidth(150);
	m_color_combo->setFixedWidth(150);
	m_save_mode->setFixedWidth(100);
	m_save->setFixedWidth(44);
	m_open->setFixedWidth(44);
	m_open_combo->setFixedWidth(100);

	m_hbox_skip->addWidget(m_skip_label);
	m_hbox_skip->addWidget(m_skip_edit);
	m_hbox_skip->setAlignment(Qt::AlignLeft);

	m_skip_progress->setOrientation(Qt::Horizontal);
	m_skip_progress->hide();

	m_color_combo->addItem("Family");
	m_color_combo->addItem("Life");
	m_color_combo->addItem("Energy");
	m_color_combo->addItem("Age");

	m_save->setEnabled(false);

	m_hbox_save->addWidget(m_save_mode);
	m_hbox_save->addWidget(m_save);
	m_hbox_save->setAlignment(Qt::AlignLeft);

	m_open_combo->addItem(RANDOM_ANIMAL);

	m_hbox_open->addWidget(m_open);
	m_hbox_open->addWidget(m_open_combo);
	m_hbox_open->setAlignment(Qt::AlignLeft);

	m_vbox_layout->addWidget(m_start_or_stop);
	m_vbox_layout->addWidget(m_skip);
	m_vbox_layout->addWidget(m_skip_progress);
	m_vbox_layout->addLayout(m_hbox_skip);
	m_vbox_layout->addWidget(m_spawn);
	m_vbox_layout->addWidget(m_clear);
	m_vbox_layout->addWidget(m_color_combo);
	m_vbox_layout->addLayout(m_hbox_save);
	m_vbox_layout->addLayout(m_hbox_open);
	m_vbox_layout->addWidget(m_group_values);
	m_vbox_layout->addWidget(m_group_features);
	m_vbox_layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	// 1 - groupbox values
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
	m_grid_values->addWidget(m_random_prob_label, 6, 0);
	m_grid_values->addWidget(m_random_prob_edit, 6, 1);
	m_grid_values->addWidget(m_erase_radius_label, 7, 0);
	m_grid_values->addWidget(m_erase_radius_edit, 7, 1);

	m_group_values->setMaximumWidth(250);

	m_group_values->setLayout(m_grid_values);
	m_group_values->setCheckable(true);
	m_group_values->setChecked(false);
	GroupValuesHide();

	// 2 - groupbox features
	m_mutation_check->setChecked(Config::GetMutation());
	m_photosynthesis_check->setChecked(Config::GetPhotosynthesis());
	m_kill_check->setChecked(Config::GetKill());
	m_alternative_check->setChecked(Config::GetAlternative());
	m_migration_check->setChecked(Config::GetMigration());
	m_migration_visible = Config::GetMigration();
	m_death_check->setChecked(Config::GetDeath());
	m_death_visible = Config::GetDeath();

	m_grid_features->addWidget(m_mutation_check, 0, 0);
	m_grid_features->addWidget(m_photosynthesis_check, 1, 0);
	m_grid_features->addWidget(m_kill_check, 2, 0);
	m_grid_features->addWidget(m_alternative_check, 3, 0);
	m_grid_features->addWidget(m_migration_check, 4, 0);
	m_grid_features->addWidget(m_migration_prob_label, 5, 0);
	m_grid_features->addWidget(m_migration_prob_edit, 5, 1);
	m_grid_features->addWidget(m_death_check, 6, 0);
	m_grid_features->addWidget(m_death_prob_label, 7, 0);
	m_grid_features->addWidget(m_death_prob_edit, 7, 1);

	m_group_features->setMaximumWidth(250);

	m_group_features->setLayout(m_grid_features);
	m_group_features->setCheckable(true);
	m_group_features->setChecked(false);
	GroupFeaturesHide();

	m_hbox_layout->addLayout(m_vbox_layout);
	m_hbox_layout->addWidget(m_statistics);
	m_hbox_layout->setAlignment(Qt::AlignLeft);

	// other
	setLayout(m_hbox_layout);

	m_painter->SetTimerInterval(Config::DEFAULT_INTERVAL);
}

void Interface::Connections() {
	// 0 - main
	connect(m_start_or_stop, &QPushButton::clicked, this, &Interface::StartOrStop);
	connect(m_skip, &QPushButton::clicked, this, &Interface::Skip);
	connect(m_spawn, &QPushButton::clicked, this, &Interface::SpawnAnimal);
	connect(m_clear, &QPushButton::clicked, this, &Interface::ClearField);
	connect(m_color_combo, &QComboBox::currentTextChanged, this, &Interface::AnimalColor);
	connect(m_save_mode, &QPushButton::clicked, this, &Interface::SaveMode);
	connect(m_save, &QPushButton::clicked, this, &Interface::Save);
	connect(m_open, &QPushButton::clicked, this, &Interface::Open);
	connect(m_open_combo, &QComboBox::currentTextChanged, this, &Interface::AnimalList);

	// 1 - groupbox values
	connect(m_group_values, &QGroupBox::clicked, this, &Interface::GroupValuesVisible);
	connect(m_timer_interval_edit, &QLineEdit::textChanged, this, &Interface::ChangeTimerInterval);
	connect(m_default_energy_edit, &QLineEdit::textChanged, this, &Interface::ChangeDefaultEnergy);
	connect(m_photosynthesis_energy_edit, &QLineEdit::textChanged, this, &Interface::ChangePhotosynthesisEnergy);
	connect(m_kill_energy_edit, &QLineEdit::textChanged, this, &Interface::ChangeKillEnergy);
	connect(m_reproduction_energy_edit, &QLineEdit::textChanged, this, &Interface::ChangeReproductionEnergy);
	connect(m_max_energy_edit, &QLineEdit::textChanged, this, &Interface::ChangeMaxEnergy);
	connect(m_random_prob_edit, &QLineEdit::textChanged, this, &Interface::ChangeRandomProb);
	connect(m_erase_radius_edit, &QLineEdit::textChanged, this, &Interface::ChangeEraseRadius);
	// 2 - groupbox features
	connect(m_group_features, &QGroupBox::clicked, this, &Interface::GroupFeaturesVisible);
	connect(m_mutation_check, &QCheckBox::clicked, this, &Interface::ChangeMutation);
	connect(m_photosynthesis_check, &QCheckBox::clicked, this, &Interface::ChangePhotosynthesis);
	connect(m_kill_check, &QCheckBox::clicked, this, &Interface::ChangeKill);
	connect(m_alternative_check, &QCheckBox::clicked, this, &Interface::ChangeAlternative);
	connect(m_migration_check, &QCheckBox::clicked, this, &Interface::MigrationVisible);
	connect(m_migration_prob_edit, &QLineEdit::textChanged, this, &Interface::ChangeMigrationProb);
	connect(m_death_check, &QCheckBox::clicked, this, &Interface::DeathVisible);
	connect(m_death_prob_edit, &QLineEdit::textChanged, this, &Interface::ChangeDeathProb);
}

// 0 - main
void Interface::StartOrStop() {
	if (m_active_status) Stop();
	else Start();

	return;
}

void Interface::Start() {
	m_start_or_stop->setText("Stop");

	m_skip->setEnabled(false);
	m_save_mode->setEnabled(false);

	m_timer_interval_edit->setEnabled(false);
	m_default_energy_edit->setEnabled(false);
	m_photosynthesis_energy_edit->setEnabled(false);
	m_kill_energy_edit->setEnabled(false);
	m_reproduction_energy_edit->setEnabled(false);
	m_max_energy_edit->setEnabled(false);
	m_random_prob_edit->setEnabled(false);

	m_migration_check->setEnabled(false);
	m_migration_prob_edit->setEnabled(false);
	m_death_check->setEnabled(false);
	m_death_prob_edit->setEnabled(false);

	ChangeTimerInterval();
	m_painter->Start();
	m_active_status ^= 1;
}

void Interface::Stop() {
	m_start_or_stop->setText("Start");

	m_skip->setEnabled(true);
	m_save_mode->setEnabled(true);

	m_timer_interval_edit->setEnabled(true);
	m_default_energy_edit->setEnabled(true);
	m_photosynthesis_energy_edit->setEnabled(true);
	m_kill_energy_edit->setEnabled(true);
	m_reproduction_energy_edit->setEnabled(true);
	m_max_energy_edit->setEnabled(true);
	m_random_prob_edit->setEnabled(true);

	m_migration_check->setEnabled(true);
	m_migration_prob_edit->setEnabled(true);
	m_death_check->setEnabled(true);
	m_death_prob_edit->setEnabled(true);

	m_painter->Pause();
	m_active_status ^= 1;
}

void Interface::Skip() {
	int skip = m_skip_edit->text().toInt();
	m_skip_progress->setRange(0, skip);
	m_skip_progress->show();
	for(int i=0;i<=skip;i++) {
		m_painter->SkipMoution(1);
		m_skip_progress->setValue(i);
	}
	m_skip_progress->hide();
	m_painter->update();
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

void Interface::SaveMode() {
	if (m_save_mode_status) {
		m_save_mode->setText("Save mode");
		m_save->setEnabled(false);
		m_start_or_stop->setEnabled(true);

		m_painter->RemoveSelection();

	}
	else {
		m_save_mode->setText("Normal mode");
		m_save->setEnabled(true);
		m_start_or_stop->setEnabled(false);

		m_painter->SelectAnimal();

	}
	m_save_mode_status ^= 1;
}

void Interface::Save() {
	QString file_path = QFileDialog::getSaveFileName(this, tr("Save animal"), qApp->applicationDirPath() + "/", tr("*.cla"));
	if (!file_path.size()) return;
	QString path = qApp->applicationDirPath();
	m_painter->SaveAnimal(file_path);
}

void Interface::Open() {
	QString file_path = QFileDialog::getOpenFileName(this, tr("Load animal"), qApp->applicationDirPath() + "/", tr("*.cla"));
	if (!file_path.size()) return;
	if (m_painter->AnimalFromFile(file_path)) {
		QString animal_name = file_path.section("/", -1, -1).section(".", 0, 0);
		m_open_combo->removeItem(m_open_combo->findText(animal_name));
		m_open_combo->addItem(animal_name);
	}
}

void Interface::AnimalList() {
	QString animal_name = m_open_combo->currentText();
	m_painter->SetAnimal(animal_name);
}

// 1 - groupbox values
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
	m_random_prob_label->hide();
	m_random_prob_edit->hide();
	m_erase_radius_label->hide();
	m_erase_radius_edit->hide();
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
	m_random_prob_label->show();
	m_random_prob_edit->show();
	m_erase_radius_label->show();
	m_erase_radius_edit->show();
}

void Interface::ChangeTimerInterval() {
	m_painter->SetTimerInterval(m_timer_interval_edit->text().toInt());
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

void Interface::ChangeRandomProb() {
	Config::SetRandomProb(m_random_prob_edit->text().toInt());
}

void Interface::ChangeEraseRadius() {
	Config::SetEracerRadius(m_erase_radius_edit->text().toInt());
}

// 2 - groupbox features
void Interface::GroupFeaturesVisible() {
	if (m_group_features_visible) GroupFeaturesHide();
	else GroupFeaturesShow();
	m_group_features_visible ^= 1;
}

void Interface::GroupFeaturesHide() {
	m_mutation_check->hide();
	m_photosynthesis_check->hide();
	m_kill_check->hide();
	m_alternative_check->hide();
	m_migration_check->hide();
	m_migration_prob_label->hide();
	m_migration_prob_edit->hide();
	m_death_check->hide();
	m_death_prob_label->hide();
	m_death_prob_edit->hide();
}

void Interface::GroupFeaturesShow() {
	m_mutation_check->show();
	m_photosynthesis_check->show();
	m_kill_check->show();
	m_alternative_check->show();
	m_migration_check->show();
	if (m_migration_visible) MigrationShow();
	m_death_check->show();
	if (m_death_visible) DeathShow();
}

void Interface::ChangeMutation() {
	Config::SetMutation(m_mutation_check->isChecked());
}

void Interface::ChangePhotosynthesis() {
	Config::SetPhotosynthesis(m_photosynthesis_check->isChecked());
}

void Interface::ChangeKill() {
	Config::SetKill(m_kill_check->isChecked());
}

void Interface::ChangeAlternative() {
	Config::SetAlternative(m_alternative_check->isChecked());
}

void Interface::MigrationVisible() {
	if (m_migration_visible) MigrationHide();
	else MigrationShow();
	m_migration_visible ^= 1;
	Config::SetMigration(m_migration_visible);
}

void Interface::MigrationHide() {
	m_migration_prob_label->hide();
	m_migration_prob_edit->hide();
}

void Interface::MigrationShow() {

	m_migration_prob_label->show();
	m_migration_prob_edit->show();
}

void Interface::ChangeMigrationProb() {
	Config::SetMigrationProb(m_migration_prob_edit->text().toInt());
}

void Interface::DeathVisible() {
	if (m_death_visible) DeathHide();
	else DeathShow();
	m_death_visible ^= 1;
	Config::SetDeath(m_death_visible);
}

void Interface::DeathHide() {
	m_death_prob_label->hide();
	m_death_prob_edit->hide();
}

void Interface::DeathShow() {
	m_death_prob_label->show();
	m_death_prob_edit->show();
}

void Interface::ChangeDeathProb() {
	Config::SetDeathProb(m_death_prob_edit->text().toInt());
}
