#include "modeltablecalibration.h"
#include <QSqlRecord>

ModelTableCalibration::ModelTableCalibration(const QString &table, const QString &parentField, QObject *parent)
  : ModelTableBase{table, parent}
  , parentField(parentField) {

  /*
  connect(this, &QSqlTableModel::rowsInserted, this, [this](const QModelIndex &parent, int first, int last) {
    qDebug() << "Вставлены строки с" << first << "по" << last;
    int afterRow = first - 1;
    int indexValue = -1;
    if (afterRow > -1) indexValue = data(afterRow, indexName).toInt();
    for (int i = first; i <= last; i++) {
      qDebug() << setData(i, this->parentField, parentValue);
      qDebug() << setData(i, this->indexName, ++indexValue);
    }
    tableView()->scrollTo(index(last, 0));
  });*/
  connect(this, &QSqlTableModel::beforeInsert, this, [this](QSqlRecord &record) {
    record.setValue(this->parentField, parentValue);
    int nextPosition = rowCount(); // Или отдельный SQL-запрос SELECT MAX(position) + 1
    record.setValue(this->indexName, nextPosition);
    qDebug() << "Подготовка к вставке записи:" << record;
  });
}

void ModelTableCalibration::setParentValue(const int &parentValue) {
  this->parentValue = parentValue;
}

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
