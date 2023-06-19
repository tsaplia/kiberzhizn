#pragma once

#include <QtCore>
#include <time.h>
#include "node.h"

class NetworkOfNodes {

private:
	std::vector<std::vector<Node*>> m_network;
	std::vector<int> m_size_of_network = { 5, 8, 6, 5 }; // test, can change

public:
	NetworkOfNodes();
	NetworkOfNodes(NetworkOfNodes* net);
	NetworkOfNodes(std::ifstream& file);
	~NetworkOfNodes();
	std::vector<double> Calculations(std::vector<double> values);
	int Mutations();
	bool Save(std::ofstream& file);
};