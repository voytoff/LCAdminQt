#include "modeltablebase.h"

ModelTableBase::ModelTableBase(const QString &table, QObject *parent)
  : QSqlTableModel{parent} {

  setEditStrategy(QSqlTableModel::OnManualSubmit);
  setTable(table);
}
