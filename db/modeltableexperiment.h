#ifndef MODELTABLEEXPERIMENT_H
#define MODELTABLEEXPERIMENT_H

#include "modeltablebase.h"
#include <QObject>

class ModelTableExperiment : public ModelTableBase {
  Q_OBJECT
public:
  explicit ModelTableExperiment(const QString &table, QObject *parent = nullptr);
  void setItemDelegates(QTableView *view) override;

protected:
  QList<StringPair> columns() const override;

signals:
};

#endif // MODELTABLEEXPERIMENT_H
