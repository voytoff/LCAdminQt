#include "modeltablebase.h"
#include "modeltablecrate.h"
#include "modeltablemodule.h"

ModelTableBase::ModelTableBase(const QString &table, QObject *parent)
  : QSqlRelationalTableModel{parent} {

  setEditStrategy(QSqlTableModel::OnManualSubmit); // OnFieldChange
  setTable(table);
}

ModelTableBase *ModelTableBase::create(documentType type, const QString &table) {
  switch (type) {
  case documentType::crate:
    return new ModelTableCrate(table);
  case documentType::module:
    return new ModelTableModule(table);
  default:
    return nullptr;
  }
}