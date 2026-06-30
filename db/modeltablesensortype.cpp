#include "modeltablesensortype.h"
#include "enumlistdelegate.h"
#include "sensorview.h"

ModelTableSensorType::ModelTableSensorType(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

void ModelTableSensorType::setItemDelegates(QTableView *view) {
  ModelTableBase::setItemDelegates(view);
  view->setItemDelegateForColumn(fieldIndex("type"), new EnumListDelegate(Enums::create<Enums::calibrationType>(Enums::calibrationTypeMap), view));
  view->setItemDelegateForColumn(fieldIndex("source"), new EnumListDelegate(Enums::create<Enums::calibrationSource>(Enums::calibrationSourceMap), view));
}

QWidget *ModelTableSensorType::createEditView(const QString &title, const QList<QAction *> &actions, QWidget *parent) {
  return new SensorView(this, "sensortype_id", Enums::sensortypecalibration, actions, title, parent);
}

QStringList ModelTableSensorType::hideFields() const {
  return{"interpolation"};
}

QList<StringPair> ModelTableSensorType::columns() const {
  return QList<StringPair> {
    {"name", "Название"},
    {"type", "Тип градуировки"},
    {"source", "Источник"},
    //{"interpolation", "Тип интерполяции"},
    {"description", "Описание"}
  };
}
