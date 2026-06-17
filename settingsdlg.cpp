#include "settingsdlg.h"
#include "settings.h"
#include "ui_settingsdlg.h"

SettingsDlg::SettingsDlg(Settings *settings, QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::SettingsDlg)
  , settings(settings) {

  ui->setupUi(this);

  ui->colorScheme->addItem("Light", ColorScheme::Light);
  ui->colorScheme->addItem("Dark", ColorScheme::Dark);
  ui->colorScheme->setCurrentIndex(settings->colorScheme()-1);

  ui->tabWidget->setCurrentIndex(0);
  ui->hostName->setText(settings->hostName());
  ui->hostPort->setText(QString::number(settings->hostPort()));
  ui->databaseName->setText(settings->databaseName());
  ui->userName->setText(settings->userName());
  ui->password->setText(settings->password());

  connect(this, &QDialog::finished, this, [this](int result) { accept(result); });
  //setWindowFlags(windowFlags() & ~Qt::WindowSystemMenuHint);
  setFixedSize(420, 260);
}

SettingsDlg::~SettingsDlg() {
  delete ui;
}

void SettingsDlg::accept(const int result) {
  if (result == QDialog::Accepted) {
    settings->colorScheme(ui->colorScheme->currentData());
    settings->hostName(ui->hostName->text());
    settings->hostPort(ui->hostPort->text().toInt());
    settings->databaseName(ui->databaseName->text());
    settings->userName(ui->userName->text());
    settings->password(ui->password->text());
  }
}
