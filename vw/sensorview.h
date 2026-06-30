#ifndef SENSORVIEW_H
#define SENSORVIEW_H

#include "complexviewbase.h"
#include "modeltablebase.h"
#include "modeltablecalibration.h"
#include <QWidget>

class SensorView : public ComplexViewBase {
  Q_OBJECT
public:
  explicit SensorView(ModelTableBase *model, const QString &foreignKey, const Enums::documentType &type, const QString &title, QWidget *parent = nullptr);

  bool isModified() const override;
  bool save() override;
  void cancel() override;
  void clear() override;
  bool hasUpDown() const override;
  /** Поднимает запись в индексированной таблице */
  void up() override;
  /** Опускает запись в индексированной таблице */
  void down() override;

  void init() override;

  ModelTableBase *calibrationModel();

private:
  QString foreignKey;
  Enums::documentType foreignType;
  ModelTableBase *addCalibrationTable();
  ModelTableCalibration *detail;
  void hideCalibrationPane(const bool &hide);

signals:
};

#endif // SENSORVIEW_H
