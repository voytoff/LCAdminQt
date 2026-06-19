#include "modeltreebase.h"

ModelTreeBase::ModelTreeBase(DB *db, const QVariantList &headers, const QStringList icons, QObject *parent)
  : QAbstractItemModel(parent)
  , db(db)
  , icons(icons) {
  // Создаем корневой скрытый элемент (Level -1)
  rootItem = new TreeItem(headers, 0, -1);
}

ModelTreeBase::~ModelTreeBase() {
  delete rootItem;
}

int ModelTreeBase::columnCount(const QModelIndex &parent) const {
  return rootItem->columnCount();
}

QVariant ModelTreeBase::getIcon(const QModelIndex &index, TreeItem *item) const {
  if (icons.length() > item->level())
    return QIcon(icons.at(item->level()));
  return QVariant();
}

QVariant ModelTreeBase::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  else if (role == Qt::DecorationRole && index.column() == 0) {
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return getIcon(index, item);
  }
  else if (role == Qt::DisplayRole) {
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data(index.column());
  }
  return QVariant();
}

Qt::ItemFlags ModelTreeBase::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;
  return QAbstractItemModel::flags(index);
}

QVariant ModelTreeBase::headerData(int section, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) return rootItem->data(section);
  return QVariant();
}

QModelIndex ModelTreeBase::index(int row, int column, const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) return QModelIndex();

  TreeItem *parentItem = parent.isValid() ? static_cast<TreeItem*>(parent.internalPointer()) : rootItem;

  // Если данные еще не загружены для этого узла, загружаем их
  if (!parentItem->isLoaded()) {
    loadChildren(parentItem);
  }

  TreeItem *childItem = parentItem->child(row);
  if (childItem) return createIndex(row, column, childItem);
  return QModelIndex();
}

QModelIndex ModelTreeBase::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex();

  TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
  TreeItem *parentItem = childItem->parentItem();

  if (parentItem == rootItem) return QModelIndex();
  return createIndex(parentItem->row(), 0, parentItem);
}

int ModelTreeBase::rowCount(const QModelIndex &parent) const {
  if (parent.column() > 0) return 0;

  TreeItem *parentItem = parent.isValid() ? static_cast<TreeItem*>(parent.internalPointer()) : rootItem;

  if (!parentItem->isLoaded()) {
    loadChildren(parentItem);
  }

  return parentItem->childCount();
}
