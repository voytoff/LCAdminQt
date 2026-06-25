#include "settingsdlg.h"
#include "mainwindow.h"
#include "db.h"
#include "settings.h"
#include "QPushButton"
#include "QPushButton"
#include "QMessageBox"

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
  ui->timeout->setValue(settings->timeout());

  connect(this, &QDialog::finished, this, [this](int result) { accept(result); });
  connect(ui->testButton, &QToolButton::clicked, this, &SettingsDlg::test);

  //setWindowFlags(windowFlags() & ~Qt::WindowSystemMenuHint);
  setFixedSize(420, 260);
}

SettingsDlg::~SettingsDlg() {
  delete ui;
}

void SettingsDlg::test() {
  DB db(DatabaseName, ui->hostName->text(), ui->hostPort->text().toInt(), ui->databaseName->text(), ui->userName->text(), ui->password->text(), ui->timeout->value());
  if (db.open()) QMessageBox::information(this, title, QString("Подключение к узлу %1:%2 выполнено успешно.").arg(ui->hostName->text(), ui->hostPort->text()));
  else QMessageBox::critical(this, title,  QString("Указаны неверные параметры для подключения к узлу %1:%2, или база данных на узле отсутствует.").arg(ui->hostName->text(), ui->hostPort->text()));
}

void SettingsDlg::accept(const int result) {
  if (result == QDialog::Accepted) {
    settings->colorScheme(ui->colorScheme->currentData());
    settings->hostName(ui->hostName->text());
    settings->hostPort(ui->hostPort->text().toInt());
    settings->databaseName(ui->databaseName->text());
    settings->userName(ui->userName->text());
    settings->password(ui->password->text());
    settings->timeout(ui->timeout->value());
  }
}
