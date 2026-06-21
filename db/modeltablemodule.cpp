#include "modeltablemodule.h"
#include <QSqlRelation>

ModelTableModule::ModelTableModule(const QString &table, QWidget *parent)
  : ModelTableBase{table, parent} {

  setHeaderData(fieldIndex("crate_id"), Qt::Horizontal, tr("Крейт"));
  setHeaderData(fieldIndex("name"), Qt::Horizontal, tr("Название"));

  setRelation(fieldIndex("crate_id"), QSqlRelation("crate", "id", "name"));
}
