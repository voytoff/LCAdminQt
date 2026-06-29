#include "customviewbase.h"
#include <QCloseEvent>
#include <QApplication>

CustomViewBase::CustomViewBase(QWidget *parent)
  : QWidget{parent}
  , settings(new Settings(this))
  , layout(new QGridLayout())
  , splitter(new QSplitter(this)) {

  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(splitter, 0, 0);
  setLayout(layout);
  setOrientation(Qt::Orientation::Horizontal);
}

void CustomViewBase::setOrientation(Qt::Orientation orientation) {
  splitter->setOrientation(orientation);
}

void CustomViewBase::addWidget(QWidget *widget) {
  splitter->addWidget(widget);
}

void CustomViewBase::addTable(Enums::documentType type, TableView *table) {
  splitter->addWidget(table);
  tables.insert(type, table);
}

void CustomViewBase::addLayout(QLayout *layout) {
  QWidget *widget = new QWidget(splitter);
  widget->setLayout(layout);
  addWidget(widget);
}

QWidget *CustomViewBase::widget() {
  return this;
}

bool CustomViewBase::isModified() const {
  return tables.isModified();
}

bool CustomViewBase::save() {
  return tables.save();
}

void CustomViewBase::cancel() {
  tables.cancel();
}

void CustomViewBase::clear() {
  tables.clear();
}

TableView *CustomViewBase::table() {
  auto w = QApplication::focusWidget();
  TableView *table = qobject_cast<TableView*>(w);
  if (!table)
    table = tables.first();
  return table;
}

QSplitter *CustomViewBase::getSplitter() {
  return splitter;
}

void CustomViewBase::closeEvent(QCloseEvent *event) {
  foreach (auto table, tables) {
    if (!table->close()) {
      event->ignore();
      return;
    }
  }
  saveLayout();
}

void CustomViewBase::showEvent(QShowEvent *event) {
  restoreLayout();
}

void CustomViewBase::restoreLayout() {
  splitter->restoreState(settings->splitter3());
}

void CustomViewBase::saveLayout() {
  settings->splitter3(splitter->saveState());
}
