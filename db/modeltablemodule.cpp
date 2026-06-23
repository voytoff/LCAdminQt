#include "modeltablemodule.h"

ModelTableModule::ModelTableModule(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

QList<StringPair> ModelTableModule::columns() const {
  return QList<StringPair> {
    {"crate_id", "Крейт"},
    {"moduletype_id", "Тип модуля"},
    {"name", "Название"},
    {"description", "Описание"}
  };
}

QList<StringPair> ModelTableModule::relations() const {
  return QList<StringPair> {
    {"crate_id", "crate;id;name"},
    {"moduletype_id", "moduletype;id;name"}
  };
}
