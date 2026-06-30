#include "db.h"
#include "modeltablebase.h"
#include "modeltablecalibration.h"
#include "modeltablecrate.h"
#include "modeltableexperiment.h"
#include "modeltablemeasureunit.h"
#include "modeltablemodule.h"
#include "modeltablesensortype.h"
#include "modeltablesensor.h"
#include "../tableview.h"

#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QSqlField>
#include <QString>
#include <QRegularExpression>

ModelTableBase::ModelTableBase(const QString &table, QObject *parent)
  : QSqlRelationalTableModel{parent, DB::instance(DatabaseName)} {

  setEditStrategy(QSqlTableModel::OnManualSubmit); // OnFieldChange
  setTable(table);
}

ModelTableBase *ModelTableBase::create(Enums::documentType type) {
  ModelTableBase* result = nullptr;
  auto tableName = Enums::string(type);
  switch (type) {
  case Enums::documentType::experiment:
    result = new ModelTableExperiment(tableName);
    break;
  case Enums::documentType::crate:
    result = new ModelTableCrate(tableName);
    break;
  case Enums::documentType::module:
    result = new ModelTableModule(tableName);
    break;
  case Enums::documentType::sensorcalibration:
    result = new ModelTableCalibration(tableName, "sensor_id");
    break;
  case Enums::documentType::sensortypecalibration:
    result = new ModelTableCalibration(tableName, "sensortype_id");
    break;
  case Enums::documentType::sensortype:
    result = new ModelTableSensorType(tableName);
    break;
  case Enums::documentType::sensor:
    result = new ModelTableSensor(tableName);
    break;
  case Enums::documentType::measureunit:
    result = new ModelTableMeasureUnit(tableName);
    break;
  default: return nullptr;
  }
  result->init(type);
  result->setJoinMode(QSqlRelationalTableModel::LeftJoin);
  result->select();
  return result;
}

QWidget *ModelTableBase::createEditView(const QString &title, const QList<QAction*> &actions, QWidget *parent) {
  TableView *table = new TableView(this, actions, title);
  // Запоминаем название таблицы
  table->setWindowTitle(title);
  return table;
}

QString ModelTableBase::title() const {
  return ((QWidget*)parent())->windowTitle();
}

Enums::documentType ModelTableBase::documentType() const {
  return type;
}

QVariant ModelTableBase::currentData(const QString &fieldName) const {
  auto i = this->tableView()->currentIndex();
  if (i.isValid()) {
    int c = fieldIndex(fieldName);
    if (c > -1)
      return data(index(i.row(), c), Qt::DisplayRole);
  }
  return {};
}

QTableView *ModelTableBase::tableView() const {
  return qobject_cast<TableView*>(parent());
}

QList<int> ModelTableBase::boolIds() const {
  QList<QString> source = boolFields();
  if (tmp.length() == 0 && source.length() > 0) {
    tmp.resize(source.length());
    std::transform(source.begin(), source.end(), tmp.begin(), [this](const QString& s) {return fieldIndex(s);});
  }
  return tmp;
}

void ModelTableBase::setItemDelegates(QTableView *tableView) {
  tableView->setItemDelegate(new QSqlRelationalDelegate(tableView));
  if (!parent())
    setParent(tableView);
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

QVariant ModelTableBase::data(const int &row, const QString &fieldName) const {
  auto i = index(row, fieldIndex(fieldName));
  if (i.isValid())
    return data(i, Qt::DisplayRole);
  return {};
}

bool ModelTableBase::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (boolIds().contains(index.column()) && role == Qt::CheckStateRole) {
    // Конвертируем клик мыши в понятный для базы данных формат (1 или 0)
    int intValue = (value.toInt() == Qt::Checked) ? 1 : 0;
    // Записываем в базу данных как обычное редактирование значения
    return QSqlRelationalTableModel::setData(index, intValue, Qt::EditRole);
  }
  if (index.isValid()) {
    auto rec = record(index.row());
    QSqlField field = rec.field(index.column());
    switch (field.metaType().id())
    {
    case QMetaType::Double: {
      auto text = value.toString();
      bool ok;
      double v = QLocale().toDouble(text, &ok);
      if (!ok) {
        for (int i = 0; i < text.length(); ++i) {
          if (text[i] == '.')  text[i] = ',';
          else if (text[i] == ',') text[i] = '.';
        }
        v = QLocale().toDouble(text, &ok);
      }
      if (ok) return QSqlRelationalTableModel::setData(index, v);
      else return QSqlRelationalTableModel::setData(index, QVariant());
    }

    case QMetaType::Int:
      return QSqlRelationalTableModel::setData(index, value.toInt());

    default:
      break;
    }
  }
  return QSqlRelationalTableModel::setData(index, value, role);
}

bool ModelTableBase::setData(const int &row, const QString &fieldName, const QVariant &value) {
  auto i = index(row, fieldIndex(fieldName));
  if (i.isValid())
    return setData(i, value, Qt::EditRole);
  return false;
}

void ModelTableBase::init(const Enums::documentType &type) {
  this->type = type;
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

const int ModelTableBase::indexColumn() const {
  return fieldIndex(indexName);
}

bool ModelTableBase::moveRow(int row, int direction) {
  // Проверяем границы
  int targetRow = row + direction;
  if (targetRow < 0 || targetRow >= rowCount()) {
    return false; // Выход за пределы таблицы
  }

  // Получаем текущие значения position двух строк
  int currentPos = data(row, indexName).toInt();
  int targetPos = data(targetRow, indexName).toInt();

  // Меняем значения позиций местами в модели
  setData(row, indexName, targetPos);
  setData(targetRow, indexName, currentPos);

  // Отправляем изменения в базу данных
  if (submitAll()) {
    // Перечитываем данные, чтобы QTableView применил сортировку
    select();
    // Возвращаем выделение на перемещенную строку
    tableView()->selectRow(targetRow);
    return true;
  }
  // Откат при ошибке БД
  revertAll();
  return false;
}