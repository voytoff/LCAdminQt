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
  switch (type) {
  case documentType::cratetype: return new ModelTableCrateType(table);
  case documentType::crate: return new ModelTableCrate(table);
  case documentType::moduletype: return new ModelTableModuleType(table);
  case documentType::module: return new ModelTableModule(table);
  case documentType::calibration: return new ModelTableCalibration(table);
  default: return nullptr;
  }
}