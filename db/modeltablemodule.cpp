#include "modeltablemodule.h"
#include <QSqlRelation>

ModelTableModule::ModelTableModule(const QString &table, QWidget *parent)
  : ModelTableBase{table, parent} {

  setHeaderData(1, Qt::Horizontal, tr("Крейт"));
  setHeaderData(2, Qt::Horizontal, tr("Название"));

  setRelation(1, QSqlRelation("crate", "id", "name"));
}
