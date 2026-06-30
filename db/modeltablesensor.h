#ifndef MODELTABLESENSOR_H
#define MODELTABLESENSOR_H

#include "modeltablebase.h"
#include <QObject>

class ModelTableSensor : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableSensor(const QString &table, QObject *parent = nullptr);
  void setItemDelegates(QTableView *view) override;
  QWidget *createEditView(const QString &title, const QList<QAction*> &actions, QWidget *parent) override;

protected:
  QList<StringPair> columns() const override;
  QList<StringPair> relations() const override;
  QStringList boolFields() const override;

};

#endif // MODELTABLESENSOR_H
