#ifndef MODELTABLEMODULETYPE_H
#define MODELTABLEMODULETYPE_H

#include "modeltablebase.h"
#include <QObject>

class ModelTableModuleType : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableModuleType(const QString &table, QObject *parent = nullptr);

protected:
  QList<StringPair> columns() const override;

signals:
};

#endif // MODELTABLEMODULETYPE_H
