#ifndef MODELTABLEBASE_H
#define MODELTABLEBASE_H

#include "../types.h"
#include "../enums.h"

#include <QSqlRelationalTableModel>
#include <QList>
#include <QTableView>

class ModelTableBase : public QSqlRelationalTableModel {
  Q_OBJECT
public:
  explicit ModelTableBase(const QString &table, QObject *parent = nullptr);
  virtual void setItemDelegates(QTableView *view);
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;

  static ModelTableBase *create(Enums::documentType type, const QString &table);
  virtual QWidget *createEditView(const QString &title, QWidget *parent);
  QString title() const;
  Enums::documentType documentType() const;

  virtual QStringList hideFields() const {return {};}

private:
  Enums::documentType type;
  QTableView *view = nullptr;
  QList<int> boolIds() const;
  mutable QList<int> tmp;

protected:
  virtual QList<StringPair> columns() const {return {};}
  virtual QList<StringPair> relations() const {return {};}
  virtual QStringList boolFields() const {return {};}
  virtual void init(const Enums::documentType &type);
};

#endif // MODELTABLEBASE_H
