#ifndef MODELTABLESENSOR_H
#define MODELTABLESENSOR_H

#include "modeltablebase.h"
#include <QObject>

class ModelTableSensor : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableSensor(const QString &table, QObject *parent = nullptr);
  void setItemDelegates(QTableView *view) override;
  //Qt::ItemFlags flags(const QModelIndex &index) const override;
  //QVariant data(const QModelIndex &index, int role) const override;
  //bool setData(const QModelIndex &index, const QVariant &value, int role) override;

protected:
  QList<StringPair> columns() const override;
  QList<StringPair> relations() const override;

};

#endif // MODELTABLESENSOR_H
