#include "node.h"

Node::Node(std::vector<Node*> directions) {
	m_directions.resize(directions.size());
	for (int i = 0; i < directions.size(); i++) {
		m_directions[i].first = directions[i];
		m_directions[i].second = Random();
	}
}

Node::Node(std::vector<Node*> directions, std::vector<double> values) {
	m_directions.resize(directions.size());
	for (int i = 0; i < directions.size(); i++) {
		m_directions[i].first = directions[i];
		m_directions[i].second = values[i];
	}
}

Node::~Node() {
	m_directions.clear();
	m_directions.shrink_to_fit();
}

void Node::ActivationFunction() { // use to converte m_input to m_output
	if (m_input > 0.4) m_output = 1;
	else if (m_input > -0.4) m_output = 0;
	else m_output = -1;
	m_input = 0;
}

void Node::AddValueToInput(double value) { // factivate = false, cuz input change and result of activate function can change
	m_input += value;
	m_factive_use = false;
}

void Node::SetValueToOutput(double value) {
	m_output = value;
	m_factive_use = true;
}

double Node::GetOutput() { // when we take output, we need calc it and call activate function
	if (!m_factive_use) {
		ActivationFunction();
		m_factive_use = true;
	}
	return m_output;
}

double Node::GetInput() {
	return m_input;
}

void Node::SetWeightMulti(double value) {
	m_weight_multi = value;
}

double Node::GetWeightMulti() {
	return m_weight_multi;
}

std::vector<double> Node::GetDirectionsValues() {
	std::vector<double> values;
	for (auto it : m_directions)
		values.push_back(it.second);
	return values;
}

void Node::Mutation() { // randon weight of node change to random value from -1 to 1 in double
	int x = rand() % m_directions.size();
	m_directions[x].second = Random();
}

void Node::Sending() {
	if (!m_factive_use) {
		ActivationFunction();
		m_factive_use = true;
	}
	for (auto it : m_directions) {
		it.first->AddValueToInput(it.second * m_output);
	}
}

double Node::Random() {
	int rand_maxi = 20000;
	double buf = (rand() % rand_maxi) - rand_maxi / 2;
	return (buf / ((double)rand_maxi / 2)) * m_weight_multi;
}