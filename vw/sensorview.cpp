#include "sensorview.h"
#include "modeltablebase.h"
#include "../tableview.h"

SensorView::SensorView(ModelTableBase *model, const QString &title, QWidget *parent)
  : CustomViewBase{parent} {

  auto *widget = new TableView(model, title);// ModelTableBase::createEditView(title, parent);
  addWidget(widget);
  addWidget(new QWidget());
}

