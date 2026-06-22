#include "modeltablecalibration.h"

ModelTableCalibration::ModelTableCalibration(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

QList<StringPair> ModelTableCalibration::columns() const {
  return QList<StringPair> {
    {"name", "Название"},
    {"source", "Источник"},
    {"type", "Тип"},
    {"active", "Используется?"},
    {"date", "Дата регистрации"}
  };
}
