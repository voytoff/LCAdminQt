#ifndef MODELTABLEMODULE_H
#define MODELTABLEMODULE_H

#include "modeltablebase.h"
#include <QWidget>

class ModelTableModule : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableModule(const QString &table, QWidget *parent = nullptr);

protected:
  QList<StringPair> columns() const override;
  QList<StringPair> relations() const override;

signals:
};

#endif // MODELTABLEMODULE_H
