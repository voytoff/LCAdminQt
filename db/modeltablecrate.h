#ifndef MODELTABLECRATE_H
#define MODELTABLECRATE_H

#include "modeltablebase.h"
#include <QWidget>

class ModelTableCrate : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableCrate(const QString &table, QWidget *parent = nullptr);

signals:
};

#endif // MODELTABLECRATE_H
