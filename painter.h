#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

#include "field.h"
#include "statistics.h"

const QString RANDOM_ANIMAL = "Random";

enum class States {paused, working, start, select_animal};
enum class AnimalColors {life, family, energy, age};

class PainterArea : public QWidget
{
    Q_OBJECT

public:
    PainterArea(Statistics* stats);
    ~PainterArea();
    const QColor water_color = QColor(100, 230, 255);
    const QColor earth_color = QColor(200, 180, 130);

    void SetTimerInterval(int value);
    void SetAnimal(QString animal_name);
    void SetAnimalColor(AnimalColors color);
    void Clear();
    void Spawn();
    void Pause();
    void Start();
    void TimerTick();
    void SkipMoution(int steps);
    void SelectAnimal();
    void RemoveSelection();
    bool AnimalSelected();
    bool SaveAnimal(QString filename);
    bool AnimalFromFile(QString filename);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Field* m_field;
    QTimer* m_timer;
    Statistics* m_stats;
    int m_width;
    int m_height;
    double m_ceil_width;
    double m_ceil_height;
    States m_state;
    AnimalColors m_animal_color = AnimalColors::family;
    bool m_right_button_pressed = false;
    QColor GetAnimalColor(Animal* animal);
    void ClearArea(int x, int y, int r);
    QMap<QString, Animal*> m_loaded_animals;
    QString m_current_animal = RANDOM_ANIMAL;

    /*Selected point features*/
    void FlasTick();
    std::pair<int,int> m_selected_cord;
    bool m_selectd_visible = false;
    QTimer* m_flash_timer;
};