#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "modeltablebase.h"
#include <QTableView>

class TableView : public QTableView
{
  Q_OBJECT
public:
  explicit TableView(ModelTableBase *model, QWidget *parent = nullptr);

signals:
};

#endif // TABLEVIEW_H
