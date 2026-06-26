#ifndef SENSORVIEW_H
#define SENSORVIEW_H

#include "customviewbase.h"
#include "modeltablebase.h"
#include <QWidget>

class SensorView : public CustomViewBase {
  Q_OBJECT
public:
  explicit SensorView(ModelTableBase *model, const QString &title, QWidget *parent = nullptr);

signals:
};

#endif // SENSORVIEW_H
