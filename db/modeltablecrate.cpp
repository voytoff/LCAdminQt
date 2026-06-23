#include "modeltablecrate.h"
#include "enumlistdelegate.h"
#include "../enums.h"
#include "spinboxdelegate.h"

ModelTableCrate::ModelTableCrate(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

void ModelTableCrate::setItemDelegates(QTableView *view) {
  view->setItemDelegateForColumn(fieldIndex("cratetype"), new EnumListDelegate(Enums::create<Enums::crateType>(), view));
  view->setItemDelegateForColumn(fieldIndex("port"), new SpinBoxDelegate(0, 65000, this));
}

QList<StringPair> ModelTableCrate::columns() const {
  return QList<StringPair> {
    {"cratetype", "Тип крейта"},
    {"name", "Название"},
    {"host", "Расположение"},
    {"port", "Порт"}
  };
}
