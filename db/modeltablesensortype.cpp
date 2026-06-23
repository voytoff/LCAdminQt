#include "modeltablesensortype.h"

ModelTableSensorType::ModelTableSensorType(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

void ModelTableSensorType::setItemDelegates(QTableView *view) {
}

QList<StringPair> ModelTableSensorType::columns() const {
  return QList<StringPair> {
    {"name", "Название"},
    {"type", "Тип градуировки"},
    {"source", "Источник"},
    {"interpolation", "Тип интерполяции"},
    {"description", "Описание"}
  };
}
