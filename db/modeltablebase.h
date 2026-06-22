#ifndef MODELTABLEBASE_H
#define MODELTABLEBASE_H

#include "../types.h"
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QList>
#include <QVariant>


class ModelTableBase : public QSqlRelationalTableModel {
  Q_OBJECT
public:
  explicit ModelTableBase(const QString &table, QObject *parent = nullptr);
  static ModelTableBase *create(documentType type, const QString &table);

protected:
  virtual QList<StringPair> columns() const {return {};}
  virtual QList<StringPair> relations() const {return {};}
  virtual void init();
};

#endif // MODELTABLEBASE_H
