#include "modeltablemeasureunit.h"

ModelTableMeasureUnit::ModelTableMeasureUnit(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

QList<StringPair> ModelTableMeasureUnit::columns() const {
  return QList<StringPair> {
    {"name", "Название"},
  };
}
