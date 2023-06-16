#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

#include "field.h"
#include "painter.h"

const int ROWS = 60;
const int COLUMNS = 60;
const int TIMER_INTERVAL = 500;


enum class States {paused, working};
enum class AnimalColors {life, family};

class PainterArea : public QWidget
{
    Q_OBJECT

public:
    PainterArea();
    ~PainterArea();
    const QColor water_color = QColor(100, 230, 255);
    const QColor earth_color = QColor(200, 180, 130);

    static void SetTimerInterval(int value);
    static void SetAnimalColor(AnimalColors color);

public slots:
    void Pause();
    void Start();
    void TimerTick();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    Field* m_field;
    QTimer* m_timer;
    inline static int m_row = 60;
    inline static int m_col = 60;
    inline static int m_timer_interval = 500;
    int m_width;
    int m_height;
    double m_ceil_width;
    double m_ceil_height;
    States m_state;
    inline static AnimalColors m_animal_color = AnimalColors::family;

};