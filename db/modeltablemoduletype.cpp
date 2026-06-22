#include "modeltablemoduletype.h"

ModelTableModuleType::ModelTableModuleType(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {

  setHeaderData(fieldIndex("name"), Qt::Horizontal, tr("Название"));
  setHeaderData(fieldIndex("depth"), Qt::Horizontal, tr("Разрядность"));
  setHeaderData(fieldIndex("interface"), Qt::Horizontal, tr("Интерфейс"));
  setHeaderData(fieldIndex("description"), Qt::Horizontal, tr("Описание"));
}
