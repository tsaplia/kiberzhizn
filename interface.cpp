#include "interface.h"

Interface::Interface(PainterArea* painter) {
	m_painter = painter;
	m_start_or_stop = new QPushButton("Start");
	m_slider_weight_multi = new QSlider(Qt::Horizontal);

	m_vbox_layout = new QVBoxLayout();

	Settings();
	Connections();

}

Interface::~Interface() {

}

void Interface::Settings() {
	m_vbox_layout->addWidget(m_start_or_stop);
	m_vbox_layout->addWidget(m_slider_weight_multi);
	setLayout(m_vbox_layout);
	setMaximumWidth(100);

	Node::SetWeightMulti(WEIGHT_MULTI);


	return;
}

void Interface::Connections() {
	connect(m_start_or_stop, &QPushButton::clicked, this, &Interface::StartOrStop);

	return;
}

void Interface::StartOrStop() {
	if (m_active_status) Stop();
	else Start();

	return;
}

void Interface::Start() {
	m_start_or_stop->setText("Stop");
	m_active_status ^= 1;
	
	return;
}

void Interface::Stop() {
	m_start_or_stop->setText("Start");
	m_active_status ^= 1;

	return;
}