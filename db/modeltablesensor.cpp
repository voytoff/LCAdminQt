#include "modeltablesensor.h"
#include "sensorview.h"

ModelTableSensor::ModelTableSensor(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

void ModelTableSensor::setItemDelegates(QTableView *view) {
  ModelTableBase::setItemDelegates(view);
  //view->setItemDelegateForColumn(fieldIndex("active"), new CheckboxDelegate(this));
}

QWidget *ModelTableSensor::createEditView(const QString &title, QWidget *parent) {
  return new SensorView(this, title, parent);
}

QList<StringPair> ModelTableSensor::columns() const {
  return QList<StringPair> {
    {"sensortype_id", "Тип датчика"},
    //{"calibration_id", "Градуировка"},
    {"sn", "Серийный номер"},
    {"active", "Используется?"},
    {"description", "Описание"}
  };
}

QList<StringPair> ModelTableSensor::relations() const {
  return QList<StringPair> {
    {"sensortype_id", "sensortype;id;name"},
    //{"calibration_id", "calibration;id;name"}
  };
}

QStringList ModelTableSensor::boolFields() const {
  return {"active"};
}
