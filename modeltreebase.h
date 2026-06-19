#ifndef MODELTREEBASE_H
#define MODELTREEBASE_H

#include "db.h"
#include "treeitem.h"
#include <QAbstractItemModel>

class ModelTreeBase : public QAbstractItemModel {
  Q_OBJECT
public:
  explicit ModelTreeBase(DB *db, const QVariantList &headers, const QStringList icons = {}, QObject *parent = nullptr);
  ~ModelTreeBase();

  QVariant data(const QModelIndex &index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

protected:
  // Логика динамической загрузки из разных таблиц в зависимости от уровня (Level)
  virtual void loadChildren(TreeItem *parentItem) const = 0;
  virtual QVariant getIcon(const QModelIndex &index, TreeItem *item) const;
  DB *db;
  TreeItem *rootItem;
  QStringList icons;

};

#endif // MODELTREEBASE_H
