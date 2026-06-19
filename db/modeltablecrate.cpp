#include "modeltablecrate.h"

ModelTableCrate::ModelTableCrate(const QString &table, QWidget *parent)
  : ModelTableBase{table, parent} {

  setHeaderData(1, Qt::Horizontal, tr("Название"));
}
