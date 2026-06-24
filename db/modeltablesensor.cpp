#include "modeltablesensor.h"

ModelTableSensor::ModelTableSensor(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

void ModelTableSensor::setItemDelegates(QTableView *view) {
  ModelTableBase::setItemDelegates(view);
  //view->setItemDelegateForColumn(fieldIndex("active"), new CheckboxDelegate(this));
}

QList<StringPair> ModelTableSensor::columns() const {
  return QList<StringPair> {
    {"sensortype_id", "Тип датчика"},
    {"calibration_id", "Градуировка"},
    {"sn", "Название"},
    {"active", "Используется?"},
    {"description", "Описание"}
  };
}

QList<StringPair> ModelTableSensor::relations() const {
  return QList<StringPair> {
    {"sensortype_id", "sensortype;id;name"},
    {"calibration_id", "calibration;id;name"}
  };
}

QStringList ModelTableSensor::boolFields() const {
  return {"active"};
}
