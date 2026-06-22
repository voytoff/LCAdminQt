#include "modeltablecratetype.h"

ModelTableCrateType::ModelTableCrateType(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {

  setHeaderData(fieldIndex("name"), Qt::Horizontal, tr("Название"));
  setHeaderData(fieldIndex("interface"), Qt::Horizontal, tr("Интерфейс"));
  setHeaderData(fieldIndex("slots"), Qt::Horizontal, tr("Количество слотов"));
  setHeaderData(fieldIndex("description"), Qt::Horizontal, tr("Описание"));
}
