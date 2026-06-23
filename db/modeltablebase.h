#ifndef MODELTABLEBASE_H
#define MODELTABLEBASE_H

#include "../types.h"
#include <QSqlRelationalTableModel>
#include <QList>
#include <QTableView>

class ModelTableBase : public QSqlRelationalTableModel {
  Q_OBJECT
public:
  explicit ModelTableBase(const QString &table, QObject *parent = nullptr);
  virtual void setItemDelegates(QTableView *view);

  static ModelTableBase *create(documentType type, const QString &table);

private:
  QTableView *view;

protected:
  virtual QList<StringPair> columns() const {return {};}
  virtual QList<StringPair> relations() const {return {};}
  virtual void init();
};

#endif // MODELTABLEBASE_H
