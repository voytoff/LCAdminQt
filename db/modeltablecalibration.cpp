#include "modeltablecalibration.h"

ModelTableCalibration::ModelTableCalibration(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

//Qt::ItemFlags ModelTableCalibration::flags(const QModelIndex &index) const {
//  return ModelTableBase::flags(index) & ~Qt::ItemIsEditable;
//}

QList<StringPair> ModelTableCalibration::columns() const {
  return {
    {"index", "#"},
    {"x", "X"},
    {"y", "Y"},
  };
}

QStringList ModelTableCalibration::hideFields() const {
  return {"sensor_id", "index"};
}
