#include "modeltablecrate.h"

ModelTableCrate::ModelTableCrate(const QString &table, QWidget *parent)
  : ModelTableBase{table, parent} {

  setHeaderData(fieldIndex("cratetype_id"), Qt::Horizontal, tr("Тип крейта"));
  setHeaderData(fieldIndex("name"), Qt::Horizontal, tr("Название"));
  setHeaderData(fieldIndex("host"), Qt::Horizontal, tr("Расположение"));
  setHeaderData(fieldIndex("port"), Qt::Horizontal, tr("Порт"));

  setRelation(fieldIndex("cratetype_id"), QSqlRelation("cratetype", "id", "name"));
}
