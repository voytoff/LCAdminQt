#include "customviewbase.h"

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

void CustomViewBase::addLayout(QLayout *layout) {
  QWidget *widget = new QWidget(splitter);
  widget->setLayout(layout);
  addWidget(widget);
}

QSplitter *CustomViewBase::getSplitter() {
  return splitter;
}

void CustomViewBase::closeEvent(QCloseEvent *event) {
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
