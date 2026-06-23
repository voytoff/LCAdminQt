#ifndef MODELTABLECRATE_H
#define MODELTABLECRATE_H

#include "modeltablebase.h"
#include <QWidget>

class ModelTableCrate : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableCrate(const QString &table, QObject *parent = nullptr);

  void setItemDelegates(QTableView *view) override;

protected:
  QList<StringPair> columns() const override;

};

#endif // MODELTABLECRATE_H
