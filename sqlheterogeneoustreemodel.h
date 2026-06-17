#ifndef SQLHETEROGENEOUSTREEMODEL_H
#define SQLHETEROGENEOUSTREEMODEL_H

#include "treeitem.h"
#include <QAbstractItemModel>
#include <QSqlQuery>

class SqlHeterogeneousTreeModel : public QAbstractItemModel {
  Q_OBJECT
public:
  explicit SqlHeterogeneousTreeModel(QObject *parent = nullptr);
  ~SqlHeterogeneousTreeModel();

  QVariant data(const QModelIndex &index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
  void loadChildren(TreeItem *parentItem) const;
  TreeItem *rootItem;
};

#endif // SQLHETEROGENEOUSTREEMODEL_H
