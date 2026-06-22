#ifndef MODELTABLECRATE_H
#define MODELTABLECRATE_H

#include "modeltablebase.h"
#include <QWidget>

class ModelTableCrate : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableCrate(const QString &table, QObject *parent = nullptr);

protected:
  QList<StringPair> columns() const override;
  QList<StringPair> relations() const override;

signals:
};

#endif // MODELTABLECRATE_H
