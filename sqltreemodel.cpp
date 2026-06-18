#include "sqltreemodel.h"
#include <QSqlError>
#include <QIcon>

SqlTreeModel::SqlTreeModel(DB *db, QObject *parent)
  : QAbstractItemModel(parent)
  , db(db) {
  // Создаем корневой скрытый элемент (Level -1)
  rootItem = new TreeItem({ "Название", "Инфо" }, 0, -1);
}

SqlTreeModel::~SqlTreeModel() {
  delete rootItem;
}

int SqlTreeModel::columnCount(const QModelIndex &parent) const {
  return rootItem->columnCount();
}

QVariant SqlTreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  else if (role == Qt::DecorationRole && index.column() == 0) {
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    if (item->level() == 0)
      return QIcon(":/images/db/crate.png");
    else if (item->level() == 1)
      return QIcon(":/images/db/module.png");
  }
  else if (role == Qt::DisplayRole) {
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data(index.column());
  }
  return QVariant();
}

Qt::ItemFlags SqlTreeModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;
  return QAbstractItemModel::flags(index);
}

QVariant SqlTreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) return rootItem->data(section);
  return QVariant();
}

QModelIndex SqlTreeModel::index(int row, int column, const QModelIndex &parent) const {
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

QModelIndex SqlTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex();

  TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
  TreeItem *parentItem = childItem->parentItem();

  if (parentItem == rootItem) return QModelIndex();
  return createIndex(parentItem->row(), 0, parentItem);
}

int SqlTreeModel::rowCount(const QModelIndex &parent) const {
  if (parent.column() > 0) return 0;

  TreeItem *parentItem = parent.isValid() ? static_cast<TreeItem*>(parent.internalPointer()) : rootItem;

  if (!parentItem->isLoaded()) {
    loadChildren(parentItem);
  }

  return parentItem->childCount();
}

// Логика динамической загрузки из разных таблиц в зависимости от уровня (Level)
void SqlTreeModel::loadChildren(TreeItem *parentItem) const {
  // Приведение к неконстантному указателю для изменения флага и добавления детей
  TreeItem *item = const_cast<TreeItem*>(parentItem);
  item->setLoaded(true);

  int nextLevel = item->level() + 1;

  // В зависимости от уровня строим соответствующий SQL-запрос
  if (nextLevel == 0) {
    // Уровень 0: Крейты
    foreach (dbCrate *i, db->crates()) {
      TreeItem *child = new TreeItem({ i->name, ":/images/tb/settings.png" }, i->id, nextLevel, item);
      item->appendChild(child);
    }
  }
  else if (nextLevel == 1) {
    // Уровень 1: LTR-Модули
    foreach (dbModule *i, db->modules(item->id())) {
      TreeItem *child = new TreeItem({ i->name, ":/images/tb/settings.png" }, i->id, nextLevel, item);
      item->appendChild(child);
    }
  }
  else {
    return; // Максимальная глубина достигнута
  }

  // Сообщаем модели, что собираемся вставить строки (для корректной работы TreeView)
  // Так как это ленивая загрузка внутри index()/rowCount(), вызываем методы аккуратно
  /*while (query.next()) {
    int id = query.value(0).toInt();
    QVector<QVariant> data = { query.value(1), query.value(2) };

    TreeItem *child = new TreeItem(data, id, nextLevel, item);
    item->appendChild(child);
  }*/
}
