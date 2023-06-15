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

    bool m_active_status = 0;

    PainterArea* m_painter;
    QPushButton* m_start_or_stop;
    QSlider* m_slider_weight_multi;

    QVBoxLayout* m_vbox_layout;

    void Settings();
    void Connections();
    void Start();
    void Stop();

private slots:
    void StartOrStop();

public:
    Interface(PainterArea* painter);
    ~Interface();
};