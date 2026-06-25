#include "docbase.h"

DocBase::DocBase(QWidget *widget, QWidget *parent)
  : DocBase(widget->windowTitle(), widget, parent) {}

DocBase::DocBase(const QString &title, QWidget *widget, QWidget *parent)
  : QDockWidget{parent} {

  setFeatures(QDockWidget::DockWidgetFeature::DockWidgetClosable);
  setAllowedAreas(Qt::DockWidgetArea::LeftDockWidgetArea);
  setWindowTitle(title);
  setWidget(widget);
}

DocBase::DocBase(const QString &title, QLayout *layout, QWidget *parent)
 : QDockWidget{parent} {

  setFeatures(QDockWidget::DockWidgetFeature::DockWidgetClosable);
  setAllowedAreas(Qt::DockWidgetArea::LeftDockWidgetArea);
  setWindowTitle(title);
  QWidget *widget = new QWidget(this);
  widget->setLayout(layout);
  setWidget(widget);
}
