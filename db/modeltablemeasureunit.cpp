#include "modeltablemeasureunit.h"

ModelTableMeasureUnit::ModelTableMeasureUnit(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

void ModelTableMeasureUnit::setItemDelegates(QTableView *view) {
}

QList<StringPair> ModelTableMeasureUnit::columns() const {
  return QList<StringPair> {
  };
}
