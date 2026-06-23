#include "modeltablesensor.h"
#include "checkboxdelegate.h"

ModelTableSensor::ModelTableSensor(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

void ModelTableSensor::setItemDelegates(QTableView *view) {
  ModelTableBase::setItemDelegates(view);
  view->setItemDelegateForColumn(fieldIndex("active"), new CheckboxDelegate(this));
}
/*
Qt::ItemFlags ModelTableSensor::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return Qt::NoItemFlags;
  // Включаем чекбокс только для столбца active
  if (index.column() == fieldIndex("active"))
    return Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;

  return QSqlRelationalTableModel::flags(index);
}

QVariant ModelTableSensor::data(const QModelIndex &index, int role) const {
  if (index.column() == fieldIndex("active")) {
    if (role == Qt::CheckStateRole)
      return index.data(Qt::DisplayRole).toBool() ? Qt::Checked : Qt::Unchecked;
    if (role == Qt::DisplayRole)
      return QVariant(); // Скрываем текст "true"/"false"
  }
  return QSqlRelationalTableModel::data(index, role);
}

bool ModelTableSensor::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (index.column() == fieldIndex("active") && role == Qt::CheckStateRole) {
    index.data(Qt::EditRole) = (value.toInt() == Qt::Checked);
    emit dataChanged(index, index);
    return true;
  }
  return QSqlRelationalTableModel::setData(index, value, role);
}
*/
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
