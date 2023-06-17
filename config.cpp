#include "config.h"

void Config::SetDefaultEnergy(int value) {
	m_default_energy = value;
}

int Config::GetDefaultEnergy() {
	return m_default_energy;
}

void Config::SetPhotosynthesisEnergy(int value) {
	m_photosynthesis_energy = value;
}

int Config::GetPhotosynthesisEnergy() {
	return m_photosynthesis_energy;
}

void Config::SetKillEnergy(int value) {
	m_kill_energy = value;
}

int Config::GetKillEnergy() {
	return m_kill_energy;
}

void Config::SetReproductionEnergy(int value) {
	m_reproduction_energy = value;
}

int Config::GetReproductionEnergy() {
	return m_reproduction_energy;
}

void Config::SetMaxEnergy(int value) {
	m_max_energy = value;
}

int Config::GetMaxEnergy() {
	return m_max_energy;
}