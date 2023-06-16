#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

#include "painter.h"
#include "node.h"

class Interface : public QWidget
{
    Q_OBJECT

private:
    int WEIGHT_MULTI = 5;
    int TIMER_INTERVAL = 500;

    bool m_active_status = 0;

    PainterArea* m_painter;
    QPushButton* m_start_or_stop;
    QLineEdit* m_timer_interval_edit;
    QComboBox* m_color_combo;
    QVBoxLayout* m_vbox_layout;

    void Settings();
    void Connections();
    void Start();
    void Stop();
    void ChangeTimerInterval();

private slots:
    void StartOrStop();
    void AnimalColor();

public:
    Interface(PainterArea* painter);
    ~Interface();
};