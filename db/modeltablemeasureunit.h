#ifndef MODELTABLEMEASUREUNIT_H
#define MODELTABLEMEASUREUNIT_H

#include "modeltablebase.h"
#include <QObject>

class ModelTableMeasureUnit : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableMeasureUnit(const QString &table, QObject *parent = nullptr);

protected:
  QList<StringPair> columns() const override;

};

#endif // MODELTABLEMEASUREUNIT_H
