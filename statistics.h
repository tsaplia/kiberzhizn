#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

class AnimalStats {
public:
	int energy;
	int age;
	int kills;
	int synthesize;
	int reproduction;
	QColor color;
	int x;
	int y;
};

class FieldStats {
public:
	int animals;
	int dead;
	int born;
};


class Statistics : public QWidget {

	Q_OBJECT

private:
	// field
	QLabel* m_field_title;
	QLabel* m_animals_label;
	QLabel* m_animals_value;
	QLabel* m_dead_label;
	QLabel* m_dead_value;
	QLabel* m_born_label;
	QLabel* m_born_value;

	QGridLayout* m_field_grid;

	// animal
	QLabel* m_animal_title;
	QLabel* m_energy_label;
	QLabel* m_energy_value;
	QLabel* m_age_label;
	QLabel* m_age_value;
	QLabel* m_kills_label;
	QLabel* m_kills_value;
	QLabel* m_synthesize_label;
	QLabel* m_synthesize_value;
	QLabel* m_reproduction_label;
	QLabel* m_reproduction_value;
	QLabel* m_color_label;
	QLabel* m_color_value;
	QLabel* m_x_label;
	QLabel* m_x_value;
	QLabel* m_y_label;
	QLabel* m_y_value;

	QGridLayout* m_animal_grid;

	QVBoxLayout* m_vbox_layout;

	void Settings();

public:
	Statistics();
	~Statistics();
	void SetFieldStats(FieldStats stats);
	void SetAnimalStats(AnimalStats stats);
	void HideAnimalStats();
};
