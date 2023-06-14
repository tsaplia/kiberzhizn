#pragma once

#include <QtCore>
#include <time.h>

class Node {

private: // variables
	double m_input = 0;
	double m_output = 0;
	bool m_factive_use = 0;
	std::vector<std::pair<Node*, double>> m_directions;
	double Random();

public: // functions
	Node(std::vector<Node*> directions);
	Node(std::vector<Node*> directions, std::vector<double> values);
	~Node();
	void ActivationFunction();
	void AddValueToInput(double value);
	void SetValueToOutput(double value);
	double GetOutput();
	double GetInput();
	std::vector<double> GetDirectionsValues();
	void Mutation();
	void Sending();
};