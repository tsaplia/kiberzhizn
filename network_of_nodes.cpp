#include "network_of_nodes.h"

NetworkOfNodes::NetworkOfNodes() { // create network
	srand(time(NULL));

	m_network.resize(m_size_of_network.size());
	for (int i = m_size_of_network.size() - 1; i >= 0; i--) {
		for (int j = 0; j < m_size_of_network[i]; j++) {
			std::vector<Node*> directions;
			if (i+1 < m_size_of_network.size()) {
				for (auto it : m_network[i + 1]) {
					directions.push_back(it);
				}
			}
			m_network[i].push_back(new Node(directions));
		}
	}
}

std::vector<double> NetworkOfNodes::Calculations(std::vector<double> values) { // calc valus through network of nodes
	for (int i = 0; i < m_size_of_network.size()-1; i++) {
		for (int j = 0; j < m_size_of_network[i]; j++) {
			if (i == 0) {
				m_network[i][j]->SetValueToOutput(values[j]);
			}
			m_network[i][j]->Sending();
		}
	}
	std::vector<double> calc_values;
	int i = m_size_of_network.size() - 1;
	for (int j = 0; j < m_size_of_network[i]; j++) {
		calc_values.push_back(m_network[i][j]->GetOutput()); // or input?
	}
	return calc_values;
}

void NetworkOfNodes::Mutations() {
	int max_mutations = 6;
	int amount = rand() % max_mutations + 1;
	for (int q = 0; q < amount; q++) {
		int i_am = rand() % m_size_of_network.size();
		int j_am = rand() % m_size_of_network[i_am];
		m_network[i_am][j_am]->Mutation();
	}

	return;
}

NetworkOfNodes::~NetworkOfNodes() {

}