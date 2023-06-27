#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

#include "painter.h"
#include "interface.h"

class CyberLife : public QWidget
{
    Q_OBJECT

private:
    PainterArea* m_painter;
    Interface* m_interface;
    QHBoxLayout* m_hbox_layout;
    QScrollArea* m_scroll_area;

public:
    CyberLife(QWidget *parent = nullptr);
    ~CyberLife();

};
