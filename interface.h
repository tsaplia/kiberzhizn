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
    int WEIGHT_MULTI = 3;
    int TIMER_INTERVAL = 500;

    bool m_active_status = 0;
    bool m_group_values_visible = 0;

    PainterArea* m_painter;
    
    QPushButton* m_start_or_stop;
    QPushButton* m_clear;
    
    QLabel* m_default_energy_label;
    QLabel* m_max_energy_label;

    QLineEdit* m_timer_interval_edit;
    QLineEdit* m_default_energy_edit;
    QLineEdit* m_max_energy_edit;
    
    QComboBox* m_color_combo;

    QGroupBox* m_group_values;
    
    QVBoxLayout* m_vbox_layout;
    QGridLayout* m_grid_values;

    void Settings();
    void Connections();
    void Start();
    void Stop();
    void ChangeTimerInterval();
    void GroupValuesHide();
    void GroupValuesShow();

private slots:
    void StartOrStop();
    void AnimalColor();
    void ClearField();
    void GroupValuesVisible();

public:
    Interface(PainterArea* painter);
    ~Interface();
};