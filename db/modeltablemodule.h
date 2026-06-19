#ifndef MODELTABLEMODULE_H
#define MODELTABLEMODULE_H

#include "modeltablebase.h"
#include <QWidget>

class ModelTableModule : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableModule(const QString &table, QWidget *parent = nullptr);

signals:
};

#endif // MODELTABLEMODULE_H
