#include "cyber_life.h"

CyberLife::CyberLife(QWidget *parent)
    : QWidget(parent) {
    m_statistics = new Statistics();
    m_painter = new PainterArea(m_statistics);
    m_interface = new Interface(m_painter);
    
    m_hbox_layout = new QHBoxLayout(this);

    m_scroll_area = new QScrollArea();

    m_scroll_area->setWidgetResizable(true);
    m_scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scroll_area->setWidget(m_interface);
    
    m_hbox_layout->addWidget(m_painter);
    m_hbox_layout->addWidget(m_scroll_area);

   

    setLayout(m_hbox_layout);
}

CyberLife::~CyberLife() {

}