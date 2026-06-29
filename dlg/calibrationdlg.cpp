#include "calibrationdlg.h"
#include "ui_calibrationdlg.h"

#include <QSqlRelationalDelegate>
#include <QPushButton>

CalibrationDlg::CalibrationDlg(ModelTableBase* model, const int &owner, QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::CalibrationDlg)
  , owner(owner)
  , model(model) {

  /// void setupUi(ModelTableBase *model, QDialog *CalibrationDlg)
  /// tableView = new TableView(model, "", CalibrationDlg);
  ui->setupUi(model, this);
  qDebug() << model->parent();
  setSizeGripEnabled(true);

  QPushButton *upButton = new QPushButton("▲");
  upButton->setFocusPolicy(Qt::NoFocus);
  ui->buttonBox->addButton(upButton, QDialogButtonBox::ActionRole);
  QPushButton *downButton = new QPushButton("▼");
  downButton->setFocusPolicy(Qt::NoFocus);
  ui->buttonBox->addButton(downButton, QDialogButtonBox::ActionRole);

  QSpacerItem *spacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  ui->buttonBox->layout()->addItem(spacer);


  connect(upButton, &QPushButton::clicked, this, &CalibrationDlg::up);
  connect(downButton, &QPushButton::clicked, this, &CalibrationDlg::down);
  connect(this, &QDialog::finished, this, &CalibrationDlg::accept);
}

CalibrationDlg::~CalibrationDlg() {
  delete ui;
}

void CalibrationDlg::up() {
  auto index = ui->tableView->currentIndex();
  if (model->moveRow(index.row(), -1))
    ui->tableView->setCurrentIndex(model->index(index.row() - 1, index.column()));
}

void CalibrationDlg::down() {
  auto index = ui->tableView->currentIndex();
  if (model->moveRow(index.row(), 1))
    ui->tableView->setCurrentIndex(model->index(index.row() + 1, index.column()));
}

void CalibrationDlg::change(const int &source, const int &dest, const int &column) {
  auto tmp =  model->data(dest, "index");
  model->setData(dest, "index", model->data(source, "index"));
  model->setData(source, "index", dest);
  model->submitAll(); // если используется OnManualSubmit
  model->select();
  ui->tableView->setCurrentIndex(model->index(dest, column));

}

void CalibrationDlg::accept(int result) {
  if (result == QDialog::Accepted) {
  }
}
