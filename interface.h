#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>

#include "painter.h"
#include "node.h"

class Interface : public QWidget
{
    Q_OBJECT

private:
    int WEIGHT_MULTI = 3;
    int TIMER_INTERVAL = 500;

    bool m_active_status = 0;
    bool m_group_values_visible = 0;

    PainterArea* m_painter;
    
    QPushButton* m_start_or_stop;
    QPushButton* m_clear;
    QPushButton* m_spawn;

    QCheckBox* m_migration_check;
    QCheckBox* m_death_check;
    
    QLabel* m_timer_interval_label;
    QLabel* m_default_energy_label;
    QLabel* m_max_energy_label;
    QLabel* m_photosynthesis_energy_label;
    QLabel* m_kill_energy_label;
    QLabel* m_reproduction_energy_label;
    QLabel* m_migration_in_act_label;
    QLabel* m_migration_prob_label;
    QLabel* m_death_prob_label;
    QLabel* m_erase_radius_label;

    QLineEdit* m_timer_interval_edit;
    QLineEdit* m_default_energy_edit;
    QLineEdit* m_photosynthesis_energy_edit;
    QLineEdit* m_kill_energy_edit;
    QLineEdit* m_reproduction_energy_edit;
    QLineEdit* m_max_energy_edit;
    QLineEdit* m_migration_in_act_edit;
    QLineEdit* m_migration_prob_edit;
    QLineEdit* m_death_prob_edit;
    QLineEdit* m_erase_radius_edit;

    QComboBox* m_color_combo;

    QGroupBox* m_group_values;
    QGroupBox* m_group_features;
    
    QVBoxLayout* m_vbox_layout;
    QGridLayout* m_grid_values;
    QGridLayout* m_grid_features;

    void Settings();
    void Connections();
    void Start();
    void Stop();
    void GroupValuesHide();
    void GroupValuesShow();
    void GroupFeaturesHide();
    void GroupFeaturesShow();
    void MigrationHide();


private slots:
    void StartOrStop();
    void SpawnAnimal();
    void ClearField();
    void AnimalColor();
    void GroupValuesVisible();
    void ChangeTimerInterval();
    void ChangeDefaultEnergy();
    void ChangePhotosynthesisEnergy();
    void ChangeKillEnergy();
    void ChangeReproductionEnergy();
    void ChangeMaxEnergy();
    void GroupFeaturesVisible();
    void MigrationVisible();
    void ChangeMigrationRate();
    void ChangeMigrationProb();
    void DeathVisible();
    void ChangeDeathProb();
    void ChangeEraseRadius();

public:
    Interface(PainterArea* painter);
    ~Interface();
};