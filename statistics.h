#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

class Statistics : public QWidget {
	Q_OBJECT
private:

public:
	Statistics();
	~Statistics();
};

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
