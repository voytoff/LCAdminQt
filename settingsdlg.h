#ifndef SETTINGSDLG_H
#define SETTINGSDLG_H

#include <QDialog>

namespace Ui {
class SettingsDlg;
}
class Settings;
class SettingsDlg : public QDialog {
  Q_OBJECT

public:
  explicit SettingsDlg(Settings* settings, QWidget *parent = nullptr);
  ~SettingsDlg();

private:
  Ui::SettingsDlg *ui;
  Settings* settings;
  void test();

  void accept(const int result);
};

#endif // SETTINGSDLG_H
