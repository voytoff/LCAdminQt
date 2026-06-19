#ifndef MODELTABLEBASE_H
#define MODELTABLEBASE_H

#include "../types.h"
#include <QSqlTableModel >
#include <QSqlRelationalTableModel >

class ModelTableBase : public QSqlRelationalTableModel {
  Q_OBJECT
public:
  explicit ModelTableBase(const QString &table, QObject *parent = nullptr);
  static ModelTableBase *create(documentType type, const QString &table);

};

#endif // MODELTABLEBASE_H
