#ifndef CALIBRATIONDLG_H
#define CALIBRATIONDLG_H

#include "modeltablebase.h"
#include <QDialog>

namespace Ui {
class CalibrationDlg;
}

class CalibrationDlg : public QDialog
{
  Q_OBJECT

public:
  explicit CalibrationDlg(ModelTableBase* model, const int &owner, QWidget *parent = nullptr);
  ~CalibrationDlg();

  ModelTableBase* model;
  int owner;

private:
  Ui::CalibrationDlg *ui;
  void up();
  void down();
  void change(const int &source, const int &dest, const int &column);
  void accept(int result);

};

#endif // CALIBRATIONDLG_H
