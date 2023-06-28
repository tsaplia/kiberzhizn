#include "statistics.h"

Statistics::Statistics() {
	// field
	m_field_title = new QLabel("Field Statistics");
	m_animals_label = new QLabel("Animals: ");
	m_animals_value = new QLabel("322");
	m_dead_label = new QLabel("Dead: ");
	m_dead_value = new QLabel("322");
	m_born_label = new QLabel("Born: ");
	m_born_value = new QLabel("322");

	m_field_grid = new QGridLayout();

	// animal
	m_animal_title = new QLabel("Animal Statistics");
	m_energy_label = new QLabel("Energy: ");
	m_energy_value = new QLabel("322");
	m_age_label = new QLabel("Age: ");
	m_age_value = new QLabel("322");
	m_kills_label = new QLabel("Kills: ");
	m_kills_value = new QLabel("322");
	m_synthesize_label = new QLabel("Synthesizes: ");
	m_synthesize_value = new QLabel("322");
	m_reproduction_label = new QLabel("Reptoductions: ");
	m_reproduction_value = new QLabel("322");
	m_color_label = new QLabel("Color: ");
	m_color_value = new QLabel("322");
	m_x_label = new QLabel("X: ");
	m_x_value = new QLabel("322");
	m_y_label = new QLabel("Y: ");
	m_y_value = new QLabel("322");

	m_animal_grid = new QGridLayout();

	// other
	m_vbox_layout = new QVBoxLayout();

	Settings();
}

Statistics::~Statistics() {

}

void Statistics::Settings() {
	// field
	m_field_grid->addWidget(m_field_title, 0, 0);
	m_field_grid->addWidget(m_animals_label, 1, 0);
	m_field_grid->addWidget(m_animals_value, 1, 1);
	m_field_grid->addWidget(m_dead_label, 2, 0);
	m_field_grid->addWidget(m_dead_value, 2, 1);
	m_field_grid->addWidget(m_born_label, 3, 0);
	m_field_grid->addWidget(m_born_value, 3, 1);
	m_field_grid->setAlignment(Qt::AlignTop);

	// animal
	m_animal_grid->addWidget(m_animal_title, 0, 0);
	m_animal_grid->addWidget(m_energy_label, 1, 0);
	m_animal_grid->addWidget(m_energy_value, 1, 1);
	m_animal_grid->addWidget(m_age_label, 2, 0);
	m_animal_grid->addWidget(m_age_value, 2, 1);
	m_animal_grid->addWidget(m_kills_label, 3, 0);
	m_animal_grid->addWidget(m_kills_value, 3, 1);
	m_animal_grid->addWidget(m_synthesize_label, 4, 0);
	m_animal_grid->addWidget(m_synthesize_value, 4, 1);
	m_animal_grid->addWidget(m_reproduction_label, 5, 0);
	m_animal_grid->addWidget(m_reproduction_value, 5, 1);
	m_animal_grid->addWidget(m_color_label, 6, 0);
	m_animal_grid->addWidget(m_color_value, 6, 1);
	m_animal_grid->addWidget(m_x_label, 7, 0);
	m_animal_grid->addWidget(m_x_value, 7, 1);
	m_animal_grid->addWidget(m_y_label, 8, 0);
	m_animal_grid->addWidget(m_y_value, 8, 1);
	m_animal_grid->setAlignment(Qt::AlignTop);
	
	// other
	m_vbox_layout->addLayout(m_field_grid);
	m_vbox_layout->addLayout(m_animal_grid);
	m_vbox_layout->setAlignment(Qt::AlignTop);
	
	setLayout(m_vbox_layout);
}