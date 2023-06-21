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

void Config::SetEracerRadius(int value) {
	m_eracer_radius = value;
}

int Config::GetEracerRadius() {
	return m_eracer_radius;
}

void Config::SetRandomProb(int value) {
	m_random_prob = value;
}

int Config::GetRandomProb() {
	return m_random_prob;
}

void Config::SetDeathProb(int value) {
	m_death_prob = value;
}

int Config::GetDeathProb() {
	return m_death_prob;
}

void Config::SetMigrationProb(int value) {
	m_migration_prob = value;
}

int Config::GetMigrationProb() {
	return m_migration_prob;
}

void Config::SetMutation(bool value) {
	m_mutation = value;
}

bool Config::GetMutation() {
	return m_mutation;
}

void Config::SetPhotosynthesis(bool value) {
	m_photosynthesis = value;
}

bool Config::GetPhotosynthesis() {
	return m_photosynthesis;
}

void Config::SetKill(bool value) {
	m_kill = value;
}

bool Config::GetKill() {
	return m_kill;
}

void Config::SetAlternative(bool value) {
	m_alternative = value;
}

bool Config::GetAlternative() {
	return m_alternative;
}

void Config::SetMigration(bool value) {
	m_migration = value;
}

bool Config::GetMigration() {
	return m_migration;
}

void Config::SetDeath(bool value) {
	m_death = value;
}

bool Config::GetDeath() {
	return m_death;
}
