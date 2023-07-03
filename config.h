#pragma once

class Config {
private:
	inline static int m_default_energy = 4;
	inline static int m_photosynthesis_energy = 4;
	inline static int m_kill_energy = 10;
	inline static int m_reproduction_energy = 10;
	inline static int m_max_energy = 60;

	inline static int m_eracer_radius = 5;
	inline static int m_random_prob = 100;
	inline static int m_migration_prob = 2;
	inline static int m_death_prob = 8;

	inline static bool m_mutation = true;
	inline static bool m_photosynthesis = true;
	inline static bool m_kill = true;
	inline static bool m_alternative = false;
	inline static bool m_migration = false;
	inline static bool m_death = true;

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
	static void SetEracerRadius(int value);
	static int GetEracerRadius();
	static void SetRandomProb(int value);
	static int GetRandomProb();
	static void SetMigrationProb(int value);
	static int GetMigrationProb();
	static void SetDeathProb(int value);
	static int GetDeathProb();
	static void SetMutation(bool value);
	static bool GetMutation();
	static void SetPhotosynthesis(bool value);
	static bool GetPhotosynthesis();
	static void SetKill(bool value);
	static bool GetKill();
	static void SetAlternative(bool value);
	static bool GetAlternative();
	static void SetMigration(bool value);
	static bool GetMigration();
	static void SetDeath(bool value);
	static bool GetDeath();


	static constexpr double WATER_LAVEL = 0.85;
	const static int MAX_AGE = 255;

	const static int MUTATION_PROBABILITY = 5;
	const static int MAX_MUTATIONS = 6;
	const static int WEIGHT_MULTI = 3; 
	static constexpr double ROTATION_ACTIVATION = 5.0;

	const static int ROWS = 120;
	const static int COLS = 160;
	const static int DEFAULT_INTERVAL = 500;

	const static int FLASH_INTERVAL = 200;
};