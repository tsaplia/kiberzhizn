#include "node.h"

Node::Node(std::vector<std::pair<Node*, double>> directions) {
	m_directions = directions;

}

void Node::ActivationFunction() { // use to converte m_input to m_output
	if (m_input > 0.4) m_output = 1;
	else if (m_input > -0.4) m_output = 0;
	else m_output = -1;
	m_input = 0;
	
	return;
}

std::vector<std::pair<Node*, double>> Node::GetDirections() {
	return m_directions;
}

void Node::AddValueToInput(double value) { // factivate = false, cuz input change and result of activate function can change
	m_input += value;
	m_factive_use = false;

	return;
}

void Node::AddValueToOutput(double value) {
	m_output += value;

	return;
}
double Node::GetOutput() { // when we take output, we need calc it and call activate function
	if (!m_factive_use) {
		ActivationFunction();
		m_factive_use = true;
	}
	return m_output;
}

void Node::Mutation() { // randon weight of node change to random value from -1 to 1 in double
	srand(time(NULL));
	int x = rand() % m_directions.size();
	int rand_maxi = 20000;
	double buf = (rand() % rand_maxi) - rand_maxi / 2;
	double rand_maxd = rand_maxi;
	m_directions[x].second = buf / (rand_maxd / 2);

	return;
}

Node::~Node() {

}