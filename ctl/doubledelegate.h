#ifndef DOUBLEDELEGATE_H
#define DOUBLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QLineEdit>

class DoubleDelegate : public QStyledItemDelegate
{
public:
  using QStyledItemDelegate::QStyledItemDelegate;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};
#endif // DOUBLEDELEGATE_H
