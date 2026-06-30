#include "modeltablesensor.h"
#include "enumlistdelegate.h"
#include "sensorview.h"

ModelTableSensor::ModelTableSensor(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

void ModelTableSensor::setItemDelegates(QTableView *view) {
  ModelTableBase::setItemDelegates(view);
  view->setItemDelegateForColumn(fieldIndex("calibration"), new EnumListDelegate(Enums::create<Enums::sensorCalibrationType>(Enums::sensorCalibrationTypeMap), view));
}

QWidget *ModelTableSensor::createEditView(const QString &title, QWidget *parent) {
  return new SensorView(this, "sensor_id", Enums::sensorcalibration, title, parent);
}

QList<StringPair> ModelTableSensor::columns() const {
  return QList<StringPair> {
    {"sensortype_id", "Тип датчика"},
    {"sn", "Серийный номер"},
    {"calibration", "Градуировка"},
    {"active", "Используется?"},
    {"description", "Описание"}
  };
}

QList<StringPair> ModelTableSensor::relations() const {
  return QList<StringPair> {
    {"sensortype_id", "sensortype;id;name"},
  };
}

QStringList ModelTableSensor::boolFields() const {
  return {"active"};
}
