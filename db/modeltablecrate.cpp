#include "modeltablecrate.h"

ModelTableCrate::ModelTableCrate(const QString &table, QWidget *parent)
  : ModelTableBase{table, parent} {
    setRelation(fieldIndex("cratetype_id"), QSqlRelation("cratetype", "id", "name"));
}

QList<StringPair> ModelTableCrate::columns() const {
  return QList<StringPair> {
    {"cratetype_id", "Тип крейта"},
    {"name", "Название"},
    {"host", "Расположение"},
    {"port", "Порт"}
  };
}

//QList<StringPair> ModelTableCrate::relations() const {
//  return QList<StringPair> {
//    {"cratetype_id", "cratetype;id;name"}
//  };
//}
