#include "complexviewbase.h"
#include <QCloseEvent>
#include <QApplication>

ComplexViewBase::ComplexViewBase(QWidget *parent)
  : QWidget{parent}
  , settings(new Settings(this))
  , layout(new QGridLayout())
  , splitter(new QSplitter(this)) {

  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(splitter, 0, 0);
  setLayout(layout);
  setOrientation(Qt::Orientation::Horizontal);
  //splitter->setCollapsible(0, false);
}

void ComplexViewBase::setOrientation(Qt::Orientation orientation) {
  splitter->setOrientation(orientation);
}

void ComplexViewBase::addWidget(QWidget *widget) {
  splitter->addWidget(widget);
}

void ComplexViewBase::addTable(Enums::documentType type, TableView *table) {
  splitter->addWidget(table);
  tables.insert(type, table);
}

void ComplexViewBase::addLayout(QLayout *layout) {
  QWidget *widget = new QWidget(splitter);
  widget->setLayout(layout);
  addWidget(widget);
}

QWidget *ComplexViewBase::widget() {
  return this;
}

bool ComplexViewBase::isModified() const {
  return tables.isModified();
}

bool ComplexViewBase::save() {
  return tables.save();
}

void ComplexViewBase::cancel() {
  tables.cancel();
}

void ComplexViewBase::clear() {
  tables.clear();
}

TableView *ComplexViewBase::table() {
  auto w = QApplication::focusWidget();
  TableView *table = qobject_cast<TableView*>(w);
  if (!table)
    table = tables.first();
  return table;
}

QSplitter *ComplexViewBase::getSplitter() {
  return splitter;
}

void ComplexViewBase::closeEvent(QCloseEvent *event) {
  foreach (auto table, tables) {
    if (!table->close()) {
      event->ignore();
      return;
    }
  }
  saveLayout();
}

void ComplexViewBase::showEvent(QShowEvent *event) {
  init();
  restoreLayout();
}

void ComplexViewBase::restoreLayout() {
  splitter->restoreState(settings->splitter3());
}

void ComplexViewBase::saveLayout() {
  settings->splitter3(splitter->saveState());
}
