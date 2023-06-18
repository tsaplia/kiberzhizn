#include "cyber_life.h"

CyberLife::CyberLife(QWidget *parent)
    : QWidget(parent) {
    m_painter = new PainterArea();
    m_interface = new Interface(m_painter);
    
    m_hbox_layout = new QHBoxLayout(this);

    m_hbox_layout->addWidget(m_painter);
    m_hbox_layout->addWidget(m_interface);


    setLayout(m_hbox_layout);
}

CyberLife::~CyberLife() {

}