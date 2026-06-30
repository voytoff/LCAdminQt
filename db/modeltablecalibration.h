#ifndef MODELTABLECALIBRATION_H
#define MODELTABLECALIBRATION_H

#include "modeltablebase.h"
#include <QObject>
#include <QString>

class ModelTableCalibration : public ModelTableBase {
  Q_OBJECT
public:
  using ModelTableBase::QSqlRelationalTableModel;
  explicit ModelTableCalibration(const QString &table, const QString &parentField, QObject *parent = nullptr);
  void setParentValue(const int &parentValue);
  void setItemDelegates(QTableView *view) override;

protected:
  QList<StringPair> columns() const override;
  QStringList hideFields() const override;
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

  QString parentField;
  int parentValue;

signals:
};

#endif // MODELTABLECALIBRATION_H
