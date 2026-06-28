#include "modeltablecalibration.h"

ModelTableCalibration::ModelTableCalibration(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

QList<StringPair> ModelTableCalibration::columns() const {
  return {
    {"index", "N"},
    {"x", "X"},
    {"y", "Y"},
  };
}

QList<StringPair> ModelTableCalibration::relations() const {
  return {
    {"sensor_id", "sensor;id;name"},
  };
}

QStringList ModelTableCalibration::hideFields() const {
  return {"sensor_id"};
}
