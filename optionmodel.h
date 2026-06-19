#ifndef OPTIONMODEL_H
#define OPTIONMODEL_H

#include "db.h"
#include "treeitem.h"
#include <QAbstractItemModel>
#include <QSqlQuery>

class OptionModel : public QAbstractItemModel {
  Q_OBJECT
public:
  explicit OptionModel(DB *db, QObject *parent = nullptr);
  ~OptionModel();

  QVariant data(const QModelIndex &index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
  DB *db;
  void loadChildren(TreeItem *parentItem) const;
  TreeItem *rootItem;
};

#endif // OPTIONMODEL_H
