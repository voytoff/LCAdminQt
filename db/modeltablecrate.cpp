#include "modeltablecrate.h"

ModelTableCrate::ModelTableCrate(const QString &table, QWidget *parent)
  : ModelTableBase{table, parent} {

  setHeaderData(fieldIndex("name"), Qt::Horizontal, tr("Название"));
}
