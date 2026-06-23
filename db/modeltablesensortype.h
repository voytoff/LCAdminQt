#ifndef MODELTABLESENSORTYPE_H
#define MODELTABLESENSORTYPE_H

#include "modeltablebase.h"
#include <QObject>

class ModelTableSensorType : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableSensorType(const QString &table, QObject *parent = nullptr);
  void setItemDelegates(QTableView *view) override;

protected:
  QList<StringPair> columns() const override;

};

#endif // MODELTABLESENSORTYPE_H
