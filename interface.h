#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

#include "painter.h"
#include "node.h"
#include "statistics.h"

class Interface : public QWidget
{
    Q_OBJECT

private:
    bool m_active_status = 0;
    bool m_save_mode_status = 0;
    bool m_group_values_visible = 0;
    bool m_group_features_visible = 0;
    bool m_migration_visible = 0;
    bool m_death_visible = 0;

    PainterArea* m_painter;
    Statistics* m_statistics;
    
    QPushButton* m_start_or_stop;
    QPushButton* m_skip;
    QPushButton* m_clear;
    QPushButton* m_spawn;
    QPushButton* m_save_mode;
    QPushButton* m_save;
    QPushButton* m_open;

    QCheckBox* m_mutation_check;
    QCheckBox* m_photosynthesis_check;
    QCheckBox* m_kill_check;
    QCheckBox* m_alternative_check;
    QCheckBox* m_migration_check;
    QCheckBox* m_death_check;
    
    QProgressBar* m_skip_progress;

    QLabel* m_skip_label;
    // 1 - groupbox values
    QLabel* m_timer_interval_label;
    QLabel* m_default_energy_label;
    QLabel* m_max_energy_label;
    QLabel* m_photosynthesis_energy_label;
    QLabel* m_kill_energy_label;
    QLabel* m_reproduction_energy_label;
    QLabel* m_random_prob_label;
    QLabel* m_erase_radius_label;
    // 2 - groupbox features
    QLabel* m_migration_prob_label;
    QLabel* m_death_prob_label;

    QLineEdit* m_skip_edit;
    // 1 - groupbox values
    QLineEdit* m_timer_interval_edit;
    QLineEdit* m_default_energy_edit;
    QLineEdit* m_photosynthesis_energy_edit;
    QLineEdit* m_kill_energy_edit;
    QLineEdit* m_reproduction_energy_edit;
    QLineEdit* m_max_energy_edit;
    QLineEdit* m_random_prob_edit;
    QLineEdit* m_erase_radius_edit;
    // 2 - groupbox features
    QLineEdit* m_migration_prob_edit;
    QLineEdit* m_death_prob_edit;

    QComboBox* m_color_combo;
    QComboBox* m_open_combo;

    QGroupBox* m_group_values;
    QGroupBox* m_group_features;
    
    QHBoxLayout* m_hbox_layout;
    QVBoxLayout* m_vbox_layout;
    QHBoxLayout* m_hbox_skip;
    QHBoxLayout* m_hbox_save;
    QHBoxLayout* m_hbox_open;
    QGridLayout* m_grid_values;
    QGridLayout* m_grid_features;

    void Settings();
    void Connections();
    void Start();
    void Stop();
    // 1 - groupbox values
    void GroupValuesHide();
    void GroupValuesShow();
    // 2 - groupbox features
    void GroupFeaturesHide();
    void GroupFeaturesShow();
    void MigrationHide();
    void MigrationShow();
    void DeathHide();
    void DeathShow();

private slots:
    void StartOrStop();
    void Skip();
    void SpawnAnimal();
    void ClearField();
    void AnimalColor();
    void SaveMode();
    void Save();
    void Open();
    void AnimalList();
    // 1 - groupbox values
    void GroupValuesVisible();
    void ChangeTimerInterval();
    void ChangeDefaultEnergy();
    void ChangePhotosynthesisEnergy();
    void ChangeKillEnergy();
    void ChangeReproductionEnergy();
    void ChangeMaxEnergy();
    void ChangeRandomProb();
    void ChangeEraseRadius();
    // 2 - groupbox features
    void GroupFeaturesVisible();
    void ChangeMutation();
    void ChangePhotosynthesis();
    void ChangeKill();
    void ChangeAlternative();
    void MigrationVisible();
    void ChangeMigrationProb();
    void DeathVisible();
    void ChangeDeathProb();

public:
    Interface(PainterArea* painter, Statistics* statistics);
    ~Interface();
};