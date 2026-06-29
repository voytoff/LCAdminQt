#ifndef SENSORVIEW_H
#define SENSORVIEW_H

#include "customviewbase.h"
#include "modeltablebase.h"
#include "modeltablecalibration.h"
#include <QWidget>

class SensorView : public CustomViewBase {
  Q_OBJECT
public:
  explicit SensorView(ModelTableBase *model, const QString &title, QWidget *parent = nullptr);

  bool isModified() const override;
  bool save() override;
  void cancel() override;
  void clear() override;

  ModelTableBase *calibrationModel();

  const Enums::documentType calibrationType = Enums::sensorcalibration;

private:
  ModelTableBase *addCalibrationTable();
  ModelTableCalibration *detail;

signals:
};

#endif // SENSORVIEW_H
