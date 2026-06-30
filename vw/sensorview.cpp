#include "sensorview.h"
#include "modeltablebase.h"
#include "../tableview.h"
#include "../mainwindow.h"

#include <QApplication>
#include <QSqlQuery>
#include <QLabel>
#include <QFrame>

SensorView::SensorView(ModelTableBase *model, const QString &foreignKey, const Enums::documentType &foreignType, const QList<QAction*> &actions, const QString &title, QWidget *parent)
  : ComplexViewBase{parent}
  , detail(nullptr)
  , foreignKey(foreignKey)
  , foreignType(foreignType) {

  auto *table = new TableView(model, actions, title);
  addTable(model->documentType(), table);

  connect(table->selectionModel(), &QItemSelectionModel::currentRowChanged, this, [model, table, this](const QModelIndex &current, const QModelIndex &previous) {
    auto tableView = tables.value(this->foreignType);
    tableView->checkData();
    auto id = model->data(current.row(), "id");
    if (id.isValid()) {
      detail->setFilter(QString("%1 = %2").arg(this->foreignKey).arg(id.toInt()));
      detail->setParentValue(id.toInt());
      detail->select();
      hideCalibrationPane(false);
    } else hideCalibrationPane(true);
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

bool SensorView::hasUpDown() const {
  return true;
}

void SensorView::up() {
  auto tableView = tables.value(foreignType);
  auto index = tableView->currentIndex();
  if (calibrationModel()->moveRow(index.row(), -1))
    tableView->setCurrentIndex(calibrationModel()->index(index.row() - 1, index.column()));
}

void SensorView::down() {
  auto tableView = tables.value(foreignType);
  auto index = tableView->currentIndex();
  if (calibrationModel()->moveRow(index.row(), 1))
    tableView->setCurrentIndex(calibrationModel()->index(index.row() + 1, index.column()));
}

void SensorView::init() {
  if (!detail) {
    // Получаем модель завизимой таблицы
    detail = qobject_cast<ModelTableCalibration*>(addCalibrationTable());
    detail->select();
    hideCalibrationPane(true);
  }
}

ModelTableBase *SensorView::calibrationModel() {
  return modeles.value(foreignType);
}

ModelTableBase* SensorView::addCalibrationTable() {
  ModelTableBase *model = ModelTableBase::create(foreignType);
  if (model) {
    model->setSort(model->fieldIndex("index"), Qt::AscendingOrder);
    model->setFilter(QString("%1 = 0").arg(foreignKey)); // пока не показываем ничего

    TableView *table = new TableView(model, MainWindow::mw()->calibrationActionGroup, "Градуировка", this);

    modeles.insert(model->documentType(), model);
    tables.insert(model->documentType(), table);
    //addTable(Enums::sensorcalibration, table);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line);
    layout->addWidget(new QLabel("Градуировка"), 0, Qt::AlignHCenter);
    layout->addWidget(table);
    addLayout(layout);
  }
  return model;
}

void SensorView::hideCalibrationPane(const bool &hide) {
  auto w = getSplitter()->widget(1);
  if (hide) w->hide();
  else w->show();
}

