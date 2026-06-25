#include "modeltableexperiment.h"
#include "datetimeeditdelegate.h"

ModelTableExperiment::ModelTableExperiment(const QString &table, QObject *parent)
  : ModelTableBase{table, parent} {}

void ModelTableExperiment::setItemDelegates(QTableView *view) {
  ModelTableBase::setItemDelegates(view);
  view->setItemDelegateForColumn(fieldIndex("startDate"), new DateTimeEditDelegate());
  view->setItemDelegateForColumn(fieldIndex("stopDate"), new DateTimeEditDelegate());
}

QList<StringPair> ModelTableExperiment::columns() const {
  return QList<StringPair> {
    {"name", "Название"},
    {"startdate", "Время начала"},
    {"stopdate", "Время остановки"},
    {"description", "Описание"}
  };
}
