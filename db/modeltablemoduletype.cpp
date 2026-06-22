#include "modeltablemoduletype.h"

ModelTableModuleType::ModelTableModuleType(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

QList<StringPair> ModelTableModuleType::columns() const {
  return QList<StringPair> {
    {"name", "Название"},
    {"depth", "Разрядность"},
    {"interface", "Интерфейс"},
    {"description", "Описание"}
  };
}
