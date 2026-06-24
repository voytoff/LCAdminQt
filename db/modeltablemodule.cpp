#include "modeltablemodule.h"
#include "enumlistdelegate.h"

ModelTableModule::ModelTableModule(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

void ModelTableModule::setItemDelegates(QTableView *view) {
  ModelTableBase::setItemDelegates(view);
  view->setItemDelegateForColumn(fieldIndex("moduletype"), new EnumListDelegate(Enums::create<Enums::moduleType>(), view));
}

QList<StringPair> ModelTableModule::columns() const {
  return QList<StringPair> {
    {"crate_id", "Крейт"},
    {"moduletype", "Тип модуля"},
    {"name", "Название"},
    {"description", "Описание"}
  };
}

QList<StringPair> ModelTableModule::relations() const {
  return QList<StringPair> {
    {"crate_id", "crate;id;name"},
  };
}
