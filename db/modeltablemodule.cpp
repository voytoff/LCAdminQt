#include "modeltablemodule.h"
#include <QSqlRelation>

ModelTableModule::ModelTableModule(const QString &table, QWidget *parent)
  : ModelTableBase{table, parent} {

  setHeaderData(fieldIndex("crate_id"), Qt::Horizontal, tr("Крейт"));
  setHeaderData(fieldIndex("moduletype_id"), Qt::Horizontal, tr("Тип модуля"));
  setHeaderData(fieldIndex("name"), Qt::Horizontal, tr("Название"));
  setHeaderData(fieldIndex("description"), Qt::Horizontal, tr("Описание"));

  setRelation(fieldIndex("crate_id"), QSqlRelation("crate", "id", "name"));
  setRelation(fieldIndex("moduletype_id"), QSqlRelation("moduletype", "id", "name"));
}
