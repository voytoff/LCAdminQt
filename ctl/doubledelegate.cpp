#include "doubledelegate.h"
#include <QLocale>

void DoubleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
  auto *lineEdit = qobject_cast<QLineEdit *>(editor);
  if (!lineEdit) return;
  bool ok;
  double value = QLocale().toDouble(lineEdit->text(), &ok);
  if (ok) model->setData(index, value);
}
