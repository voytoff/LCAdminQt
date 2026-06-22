#include "modeltablecratetype.h"

ModelTableCrateType::ModelTableCrateType(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

QList<StringPair> ModelTableCrateType::columns() const {
  return QList<StringPair> {
    {"name", "Название"},
    {"interface", "Интерфейс"},
    {"slots", "Количество слотов"},
    {"description", "Описание"}
  };
}
