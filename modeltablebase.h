#ifndef MODELTABLEBASE_H
#define MODELTABLEBASE_H

#include <QSqlTableModel >

class ModelTableBase : public QSqlTableModel {
  Q_OBJECT
public:
  explicit ModelTableBase(const QString &table, QObject *parent = nullptr);

};

#endif // MODELTABLEBASE_H
