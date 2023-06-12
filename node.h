#pragma once

#include <QtCore>
#include <time.h>

class Node {

private: // variables
	double m_input = 0;
	double m_output = 0;
	bool m_factive_use = 0;
	std::vector<std::pair<Node*, double>> m_directions;

public: // functions
	Node(std::vector<std::pair<Node*, double>> directions);
	~Node();
	void ActivationFunction();
	std::vector<std::pair<Node*, double>> GetDirections();
	void AddValueToInput(double value);
	void AddValueToOutput(double value);
	double GetOutput();
	void Mutation();
};