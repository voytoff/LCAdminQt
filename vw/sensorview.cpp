#include "sensorview.h"
#include "modeltablebase.h"
#include "../tableview.h"

#include <QApplication>
#include <QSqlQuery>
#include <QLabel>
#include <QFrame>

SensorView::SensorView(ModelTableBase *model, const QString &title, QWidget *parent)
  : CustomViewBase{parent} {

  auto *table = new TableView(model, title);// ModelTableBase::createEditView(title, parent);
  addTable(model->documentType(), table);
  // Получаем модель завизимой таблицы
  auto detail = addCalibrationTable();
  detail->select();

  connect(table->selectionModel(), &QItemSelectionModel::currentRowChanged, this, [model, detail, table](const QModelIndex &current, const QModelIndex &previous) {
    auto id = model->data(model->index(current.row(), table->index("id"), QModelIndex()), Qt::DisplayRole);
    if (id.isValid())
      detail->setFilter(QString("sensor_id = %1").arg(id.toInt()));
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
  ModelTableBase *model = ModelTableBase::create(calibrationType);
  if (model) {
    model->setSort(model->fieldIndex("index"), Qt::AscendingOrder);
    model->setFilter("sensor_id = 0"); // пока не показываем никого
    TableView *table = new TableView(model, "Градуировки", this);
    // Делаем таблицу нередактируемой
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //addTable(Enums::sensorcalibration, table);

    modeles.insert(model->documentType(), model);
    tables.insert(model->documentType(), table);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new QLabel("Градуировки"));
    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line);
    layout->addWidget(table);
    addLayout(layout);
  }
  return model;
}

