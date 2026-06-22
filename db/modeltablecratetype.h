#ifndef MODELTABLECRATETYPE_H
#define MODELTABLECRATETYPE_H

#include "modeltablebase.h"
#include <QObject>

class ModelTableCrateType : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableCrateType(const QString &table, QObject *parent = nullptr);

protected:
  QList<StringPair> columns() const override;

signals:
};

#endif // MODELTABLECRATETYPE_H
