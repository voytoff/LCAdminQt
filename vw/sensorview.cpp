#include "sensorview.h"
#include "modeltablebase.h"
#include "../tableview.h"

#include <QApplication>

SensorView::SensorView(ModelTableBase *model, const QString &title, QWidget *parent)
  : CustomViewBase{parent} {

  auto *table = new TableView(model, title);// ModelTableBase::createEditView(title, parent);
  addTable(model->documentType(), table);
  auto detail = addCalibrationTable();

  connect(table->selectionModel(), &QItemSelectionModel::currentRowChanged, this, [model, detail, table](const QModelIndex &current, const QModelIndex &previous) {
    auto id = model->data(model->index(current.row(), table->index("id"), QModelIndex()), Qt::DisplayRole);
    if (id.isValid())
      detail->setFilter(QString("sensor_id==%1").arg(id.toInt()));
  });
}

bool SensorView::isModified() const {
  return tables.isModified();
}

bool SensorView::save() {
  return tables.save();
}

void SensorView::cancel() {
  tables.cancel();
}

void SensorView::clear() {
  tables.clear();
}

ModelTableBase* SensorView::addCalibrationTable() {
  ModelTableBase *model = ModelTableBase::create(Enums::sensorcalibration, "sensorcalibration");
  if (model) {
    model->setFilter("");
    TableView *table = new TableView(model, "Градуировки", this);
    addTable(Enums::sensorcalibration, table);
  }
  return model;
}

