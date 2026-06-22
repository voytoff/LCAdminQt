#include "modeltablebase.h"
#include "modeltablecalibration.h"
#include "modeltablecrate.h"
#include "modeltablecratetype.h"
#include "modeltablemodule.h"
#include "modeltablemoduletype.h"

ModelTableBase::ModelTableBase(const QString &table, QObject *parent)
  : QSqlRelationalTableModel{parent} {

  setEditStrategy(QSqlTableModel::OnManualSubmit); // OnFieldChange
  setTable(table);
  select();
}

ModelTableBase *ModelTableBase::create(documentType type, const QString &table) {
  ModelTableBase* result = nullptr;
  switch (type) {
  case documentType::cratetype:
    result = new ModelTableCrateType(table);
    break;
  case documentType::crate:
    result = new ModelTableCrate(table);
    break;
  case documentType::moduletype:
    result = new ModelTableModuleType(table);
    break;
  case documentType::module:
    result = new ModelTableModule(table);
    break;
  case documentType::calibration:
    result = new ModelTableCalibration(table);
    break;
  default: return nullptr;
  }
  result->init();
  return result;
}

void ModelTableBase::init() {
  foreach (auto column, columns()) {
    int index = fieldIndex(column.first);
    if (index > -1)
      setHeaderData(index, Qt::Horizontal, column.second);
  }

  foreach (auto relation, relations()) {
    int index = fieldIndex(relation.first);
    if (index > -1) {
      auto p = relation.second.split(";");
      setRelation(index, QSqlRelation(p.at(0), p.at(1), p.at(2)));
    }
  }
}