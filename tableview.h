#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "modeltablebase.h"
#include <QTableView>

class TableView : public QTableView
{
  Q_OBJECT
public:
  explicit TableView(ModelTableBase *model, QWidget *parent = nullptr);

  int index(const QString & fieldName) const;

private:
  ModelTableBase *model;

signals:
};

#endif // TABLEVIEW_H
