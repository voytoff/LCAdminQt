#ifndef MODELTABLECALIBRATION_H
#define MODELTABLECALIBRATION_H

#include "modeltablebase.h"
#include <QObject>

class ModelTableCalibration : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableCalibration(const QString &table, QObject *parent = nullptr);

signals:
};

#endif // MODELTABLECALIBRATION_H
