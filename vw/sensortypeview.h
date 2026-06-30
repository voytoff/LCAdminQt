#ifndef SENSORTYPEVIEW_H
#define SENSORTYPEVIEW_H

#include "sensorview.h"
#include <QWidget>

class SensorTypeView : public SensorView
{
  Q_OBJECT
public:
  explicit SensorTypeView(ModelTableBase *model, const QString &foreignKey, const Enums::documentType &foreignType, const QString &title, QWidget *parent = nullptr);

signals:
};

#endif // SENSORTYPEVIEW_H
