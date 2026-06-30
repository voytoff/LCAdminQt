#include "modeltablecalibration.h"
#include "doubledelegate.h"

ModelTableCalibration::ModelTableCalibration(const QString &table, const QString &parentField, QObject *parent)
  : ModelTableBase{table, parent}
  , parentField(parentField) {}

void ModelTableCalibration::setParentValue(const int &parentValue) {
  this->parentValue = parentValue;
}

void ModelTableCalibration::setItemDelegates(QTableView *view) {
  ModelTableBase::setItemDelegates(view);
  view->setItemDelegateForColumn(fieldIndex("x"), new DoubleDelegate(view));
  view->setItemDelegateForColumn(fieldIndex("y"), new DoubleDelegate(view));
}

QList<StringPair> ModelTableCalibration::columns() const {
  return {
    {"index", "#"},
    {"x", "X"},
    {"y", "Y"},
  };
}

QStringList ModelTableCalibration::hideFields() const {
  return {"sensortype_id", "sensor_id", "index"};
}

bool ModelTableCalibration::insertRows(int row, int count, const QModelIndex &parent) {
  //Q_UNUSED(parent);
  if (!QSqlRelationalTableModel::insertRows(row, count, parent))
    return false;
  for (int r = row; r < row + count; ++r) {
    qDebug() << setData(r, this->parentField, parentValue);
    qDebug() << setData(r, this->indexName, row);
  }
  // + пересчитать полностью !equals =
  return true;
}
