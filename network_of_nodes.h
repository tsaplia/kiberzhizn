#pragma once

#include <QtCore>
#include <time.h>
#include "node.h"

class NetworkOfNodes {

private:
	std::vector<std::vector<Node*>> m_network;
	std::vector<int> m_size_of_network = { 4, 5, 5, 5 }; // test, can change

public:
	NetworkOfNodes();
	~NetworkOfNodes();
	std::vector<double> Calculations(std::vector<double> values);
	void Mutations();
};