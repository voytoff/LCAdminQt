#ifndef MODELTABLECALIBRATION_H
#define MODELTABLECALIBRATION_H

#include "modeltablebase.h"
#include <QObject>
#include <QString>

class ModelTableCalibration : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableCalibration(const QString &table, const QString &parentField, QObject *parent = nullptr);
  void setParentValue(const int &parentValue);

protected:
  QList<StringPair> columns() const override;
  QStringList hideFields() const override;

  QString parentField;
  int parentValue;

signals:
};

#endif // MODELTABLECALIBRATION_H
