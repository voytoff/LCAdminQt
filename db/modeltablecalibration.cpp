#include "modeltablecalibration.h"
#include "dateeditdelegate.h"
#include "enumlistdelegate.h"
#include "../enums.h"

ModelTableCalibration::ModelTableCalibration(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

void ModelTableCalibration::setItemDelegates(QTableView *view) {
  ModelTableBase::setItemDelegates(view);
  view->setItemDelegateForColumn(fieldIndex("type"), new EnumListDelegate(Enums::create<Enums::calibrationType>(Enums::calibrationTypeMap), view));
  view->setItemDelegateForColumn(fieldIndex("source"), new EnumListDelegate(Enums::create<Enums::calibrationSource>(Enums::calibrationSourceMap), view));
  view->setItemDelegateForColumn(fieldIndex("interpolation"), new EnumListDelegate(Enums::create<Enums::calibrationSource>(Enums::interpolationTypeMap), view));
  view->setItemDelegateForColumn(fieldIndex("date"), new DateEditDelegate());
}

QList<StringPair> ModelTableCalibration::columns() const {
  return QList<StringPair> {
    {"name", "Название"},
    {"type", "Тип"},
    {"source", "Источник"},
    {"interpolation", "Интерполяция"},
    {"active", "Используется?"},
    {"date", "Дата регистрации"},
    {"description", "Описание"}
  };
}

QStringList ModelTableCalibration::boolFields() const {
  return {"active"};
}
