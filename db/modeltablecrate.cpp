#include "modeltablecrate.h"

ModelTableCrate::ModelTableCrate(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

QList<StringPair> ModelTableCrate::columns() const {
  return QList<StringPair> {
    {"cratetype_id", "Тип крейта"},
    {"name", "Название"},
    {"host", "Расположение"},
    {"port", "Порт"}
  };
}

QList<StringPair> ModelTableCrate::relations() const {
  return QList<StringPair> {
    {"cratetype_id", "cratetype;id;name"}
  };
}
