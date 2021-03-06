// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "citra_qt/configuration/configure_general.h"
#include "citra_qt/ui_settings.h"
#include "core/core.h"
#include "core/settings.h"
#include "ui_configure_general.h"
#include "common/file_util.h"

ConfigureGeneral::ConfigureGeneral(QWidget* parent)
    : QWidget(parent), ui(new Ui::ConfigureGeneral) {

    ui->setupUi(this);

    for (auto theme : UISettings::themes) {
        ui->theme_combobox->addItem(theme.first, theme.second);
    }

    this->setConfiguration();

    ui->toggle_cpu_jit->setEnabled(!Core::System::GetInstance().IsPoweredOn());
    ui->toggle_new3ds->setEnabled(!Core::System::GetInstance().IsPoweredOn());
        
    if (FileUtil::Exists(FileUtil::GetUserPath(D_SDMC_IDX) + "Nintendo 3DS/00000000000000000000000000000000/00000000000000000000000000000000/extdata/00000000/00001A03/user/course220")) {
    ui->enable_smm_fix->setVisible(true);
    } else if (FileUtil::Exists(FileUtil::GetUserPath(D_SDMC_IDX) + "Nintendo 3DS/00000000000000000000000000000000/00000000000000000000000000000000/extdata/00000000/00001A04/user/course220")) {
    ui->enable_smm_fix->setVisible(true);
    } else if (FileUtil::Exists(FileUtil::GetUserPath(D_SDMC_IDX) + "Nintendo 3DS/00000000000000000000000000000000/00000000000000000000000000000000/extdata/00000000/00001A05/user/course220")) {
    ui->enable_smm_fix->setVisible(true);
    }
    ui->updateBox->setVisible(UISettings::values.updater_found);
}

ConfigureGeneral::~ConfigureGeneral() {}

void ConfigureGeneral::setConfiguration() {
    ui->toggle_deepscan->setChecked(UISettings::values.gamedir_deepscan);
    ui->toggle_check_exit->setChecked(UISettings::values.confirm_before_closing);
    ui->toggle_cpu_jit->setChecked(Settings::values.use_cpu_jit);
    ui->toggle_new3ds->setChecked(Settings::values.is_new_3ds);

    ui->toggle_update_check->setChecked(UISettings::values.check_for_update_on_start);
    ui->toggle_auto_update->setChecked(UISettings::values.update_on_close);

    // The first item is "auto-select" with actual value -1, so plus one here will do the trick
    ui->region_combobox->setCurrentIndex(Settings::values.region_value + 1);

    ui->theme_combobox->setCurrentIndex(ui->theme_combobox->findData(UISettings::values.theme));
    ui->enable_experimental_fixes->setChecked(Settings::values.enable_experimental_fixes);
    ui->enable_smm_fix->setChecked(Settings::values.enable_smm_fix);
}

void ConfigureGeneral::applyConfiguration() {
    UISettings::values.gamedir_deepscan = ui->toggle_deepscan->isChecked();
    UISettings::values.confirm_before_closing = ui->toggle_check_exit->isChecked();
    UISettings::values.theme =
        ui->theme_combobox->itemData(ui->theme_combobox->currentIndex()).toString();
    
    UISettings::values.check_for_update_on_start = ui->toggle_update_check->isChecked();
    UISettings::values.update_on_close = ui->toggle_auto_update->isChecked();

    Settings::values.region_value = ui->region_combobox->currentIndex() - 1;
    Settings::values.use_cpu_jit = ui->toggle_cpu_jit->isChecked();
    Settings::values.is_new_3ds = ui->toggle_new3ds->isChecked();
    Settings::values.enable_experimental_fixes = ui->enable_experimental_fixes->isChecked();
    Settings::values.enable_smm_fix = ui->enable_smm_fix->isChecked();
    Settings::Apply();
}
