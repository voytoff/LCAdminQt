#ifndef MODELTABLEBASE_H
#define MODELTABLEBASE_H

#include "../types.h"
#include "../enums.h"

#include <QSqlRelationalTableModel>
#include <QList>
#include <QTableView>

class ModelTableBase : public QSqlRelationalTableModel {
  Q_OBJECT
protected:
  explicit ModelTableBase(const QString &table, QObject *parent = nullptr);

public:
  virtual void setItemDelegates(QTableView *tableView);
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant data(const int &row, const QString &fieldName) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  bool setData(const int &row, const QString &fieldName, const QVariant &value);
  /** Создает и возвращает модель по типу в параметре type */
  static ModelTableBase *create(Enums::documentType type);
  /**
   *  Создает и возвращает об'ект редактирования с интерфейсом IStateWidget.
   *  Это может быть таблица TableView или комплексный редактор CustomViewBase
  */
  virtual QWidget *createEditView(const QString &title, QWidget *parent);
  QString title() const;
  Enums::documentType documentType() const;
  QVariant currentData(const QString &fieldName) const;

  virtual QStringList hideFields() const {return {};}

private:
  Enums::documentType type;
  QTableView *tableView() const;
  QList<int> boolIds() const;
  mutable QList<int> tmp;

protected:
  virtual QList<StringPair> columns() const {return {};}
  virtual QList<StringPair> relations() const {return {};}
  virtual QStringList boolFields() const {return {};}
  virtual void init(const Enums::documentType &type);
};

#endif // MODELTABLEBASE_H
