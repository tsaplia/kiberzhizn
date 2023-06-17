#pragma once

class Config {
private:
	inline static int m_default_energy = 4;
	inline static int m_photosynthesis_energy = 4;
	inline static int m_kill_energy = 10;
	inline static int m_reproduction_energy = 10;
	inline static int m_max_energy = 60;

public:
	static void SetDefaultEnergy(int value);
	static int GetDefaultEnergy();
	static void SetPhotosynthesisEnergy(int value);
	static int GetPhotosynthesisEnergy();
	static void SetKillEnergy(int value);
	static int GetKillEnergy();
	static void SetReproductionEnergy(int value);
	static int GetReproductionEnergy();
	static void SetMaxEnergy(int value);
	static int GetMaxEnergy();
};