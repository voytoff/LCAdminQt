#ifndef SENSORVIEW_H
#define SENSORVIEW_H

#include "customviewbase.h"
#include "modeltablebase.h"
#include <QWidget>

class SensorView : public CustomViewBase {
  Q_OBJECT
public:
  explicit SensorView(ModelTableBase *model, const QString &title, QWidget *parent = nullptr);

  bool isModified() const override;
  bool save() override;
  void cancel() override;
  void clear() override;

private:
  ModelTableBase *addCalibrationTable();

signals:
};

#endif // SENSORVIEW_H
