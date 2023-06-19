#include "animal.h"
#include "network_of_nodes.h"
#include <fstream>
#include <string>

bool writeVector(const std::vector<double>& data, std::ofstream& file) {
    if (!file.is_open()) return false;

    size_t size = data.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    file.write(reinterpret_cast<const char*>(data.data()), size * sizeof(double));
    return true;
}

bool readVector(std::vector<double>& data, std::ifstream& file) {
    if (!file) return false;

    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    data.resize(size);
    file.read(reinterpret_cast<char*>(data.data()), size * sizeof(double));
    return true;
}

bool writeNumber(int n, std::ofstream& file) {
    if (!file.is_open()) return false;

    file.write(reinterpret_cast<const char*>(&n), sizeof(n));
    return true;
}

bool readNumber(int& n, std::ifstream& file) {
    if (!file) return false;

    file.read(reinterpret_cast<char*>(&n), sizeof(n));
    return true;
}

bool Animal::Save(std::string filename) {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);

    bool ok = true;
    ok &= m_brain->Save(file);
    ok &= writeNumber(static_cast<int>(m_color.rgb()), file);
    ok &= writeNumber(static_cast<int>(m_direction), file);

    file.close();
    return ok;
}

Animal* Animal::FromFile(int x, int y, Field* parent, std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    NetworkOfNodes* brain = new NetworkOfNodes(file);
    if (!brain) return nullptr;

    int color_value;
    if (!readNumber(color_value, file)) return nullptr;
    QColor color = QColor::fromRgba(color_value);

    int direction;
    if (!readNumber(direction, file)) return nullptr;

    file.close();
    return new Animal(x, y, parent, brain, QColor::fromRgba(color_value), AnimalDirections(direction));
}

bool NetworkOfNodes::Save(std::ofstream& file) {
    for (int i = m_size_of_network.size() - 2; i >= 0; i--) {
        for (int j = 0; j < m_size_of_network[i]; j++) {
            std::vector<double> values = m_network[i][j]->GetDirectionsValues();
            if (!writeVector(values, file)) return false;
        }
    }
    return true;
}

NetworkOfNodes::NetworkOfNodes(std::ifstream& file) {
    m_network.resize(m_size_of_network.size());
    for (int i = m_size_of_network.size() - 1; i >= 0; i--) {
        for (int j = 0; j < m_size_of_network[i]; j++) {
            std::vector<Node*> directions;
            std::vector<double> values;
            if (i + 1 < m_size_of_network.size()) {
                readVector(values, file);
                for (auto it : m_network[i + 1]) {
                    directions.push_back(it);
                }
            }
            m_network[i].push_back(new Node(directions, values));
        }
    }
}


