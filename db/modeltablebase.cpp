#include "db.h"
#include "modeltablebase.h"
#include "modeltablecalibration.h"
#include "modeltablecrate.h"
#include "modeltableexperiment.h"
#include "modeltablemeasureunit.h"
#include "modeltablemodule.h"
#include "modeltablesensortype.h"
#include "modeltablesensor.h"

#include <QSqlRelationalDelegate>

ModelTableBase::ModelTableBase(const QString &table, QObject *parent)
  : QSqlRelationalTableModel{parent, DB::instance(DatabaseName)} {

  setEditStrategy(QSqlTableModel::OnManualSubmit); // OnFieldChange
  setTable(table);
}

ModelTableBase *ModelTableBase::create(Enums::documentType type, const QString &table) {
  ModelTableBase* result = nullptr;
  switch (type) {
  case Enums::documentType::experiment:
    result = new ModelTableExperiment(table);
    break;
  case Enums::documentType::crate:
    result = new ModelTableCrate(table);
    break;
  //case Enums::documentType::moduletype:
  //  result = new ModelTableModuleType(table);
  //  break;
  case Enums::documentType::module:
    result = new ModelTableModule(table);
    break;
  case Enums::documentType::calibration:
    result = new ModelTableCalibration(table);
    break;
  case Enums::documentType::sensortype:
    result = new ModelTableSensorType(table);
    break;
  case Enums::documentType::sensor:
    result = new ModelTableSensor(table);
    break;
  case Enums::documentType::measureunit:
    result = new ModelTableMeasureUnit(table);
    break;
  default: return nullptr;
  }
  result->init();
  result->setJoinMode(QSqlRelationalTableModel::LeftJoin);
  result->select();
  return result;
}

QList<int> ModelTableBase::boolIds() const {
  QList<QString> source = boolFields();
  if (tmp.length() == 0 && source.length() > 0) {
    tmp.resize(source.length());
    std::transform(source.begin(), source.end(), tmp.begin(), [this](const QString& s) {return fieldIndex(s);});
  }
  return tmp;
}

void ModelTableBase::setItemDelegates(QTableView *view) {
  view->setItemDelegate(new QSqlRelationalDelegate(view));
}

Qt::ItemFlags ModelTableBase::flags(const QModelIndex &index) const {
  if (boolIds().contains(index.column()))
    return Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  return QSqlRelationalTableModel::flags(index);
}

QVariant ModelTableBase::data(const QModelIndex &index, int role) const {
  if (boolIds().contains(index.column())) {
    QVariant rawValue = QSqlRelationalTableModel::data(index, Qt::DisplayRole);
    // Безопасно приведим tinyint к bool (0 - false, всё остальное - true)
    bool isTrue = rawValue.isValid() && !rawValue.isNull() && (rawValue.toInt() != 0);
    if (role == Qt::CheckStateRole)
      return isTrue ? Qt::Checked : Qt::Unchecked;
    else if (role == Qt::DisplayRole || role == Qt::EditRole)
      // Возвращаем пустую строку, чтобы поверх чекбокса не писались цифры 0 или 1
      return QVariant();
  }
  return QSqlRelationalTableModel::data(index, role);
}

bool ModelTableBase::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (boolIds().contains(index.column()) && role == Qt::CheckStateRole) {
    // Конвертируем клик мыши в понятный для базы данных формат (1 или 0)
    int intValue = (value.toInt() == Qt::Checked) ? 1 : 0;
    // Записываем в базу данных как обычное редактирование значения
    return QSqlRelationalTableModel::setData(index, intValue, Qt::EditRole);
  }
  return QSqlRelationalTableModel::setData(index, value, role);
}

void ModelTableBase::init() {
  foreach (auto relation, relations()) {
    int index = fieldIndex(relation.first);
    if (index > -1) {
      auto p = relation.second.split(";");
      setRelation(index, QSqlRelation(p.at(0), p.at(1), p.at(2)));
    }
  }
  foreach (auto column, columns()) {
    int index = fieldIndex(column.first);
    if (index > -1)
      setHeaderData(index, Qt::Horizontal, column.second);
  }
}