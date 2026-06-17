#include "sqlheterogeneoustreemodel.h"
#include <QSqlError>
#include <QDebug>

SqlHeterogeneousTreeModel::SqlHeterogeneousTreeModel(QObject *parent) : QAbstractItemModel(parent) {
  // Создаем корневой скрытый элемент (Level -1)
  rootItem = new TreeItem({ "Название", "Доп. Инфо" }, 0, -1);
}

SqlHeterogeneousTreeModel::~SqlHeterogeneousTreeModel() {
  delete rootItem;
}

int SqlHeterogeneousTreeModel::columnCount(const QModelIndex &parent) const {
  return rootItem->columnCount();
}

QVariant SqlHeterogeneousTreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || role != Qt::DisplayRole) return QVariant();
  TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
  return item->data(index.column());
}

Qt::ItemFlags SqlHeterogeneousTreeModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;
  return QAbstractItemModel::flags(index);
}

QVariant SqlHeterogeneousTreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) return rootItem->data(section);
  return QVariant();
}

QModelIndex SqlHeterogeneousTreeModel::index(int row, int column, const QModelIndex &parent) const {
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

QModelIndex SqlHeterogeneousTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex();

  TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
  TreeItem *parentItem = childItem->parentItem();

  if (parentItem == rootItem) return QModelIndex();
  return createIndex(parentItem->row(), 0, parentItem);
}

int SqlHeterogeneousTreeModel::rowCount(const QModelIndex &parent) const {
  if (parent.column() > 0) return 0;

  TreeItem *parentItem = parent.isValid() ? static_cast<TreeItem*>(parent.internalPointer()) : rootItem;

  if (!parentItem->isLoaded()) {
    loadChildren(parentItem);
  }

  return parentItem->childCount();
}

// Логика динамической загрузки из разных таблиц в зависимости от уровня (Level)
void SqlHeterogeneousTreeModel::loadChildren(TreeItem *parentItem) const {
  // Приведение к неконстантному указателю для изменения флага и добавления детей
  TreeItem *item = const_cast<TreeItem*>(parentItem);
  item->setLoaded(true);

  int nextLevel = item->level() + 1;
  QSqlQuery query;

  // В зависимости от уровня строим соответствующий SQL-запрос
  if (nextLevel == 0) {
    // Уровень 0: Корневые элементы (например, "Компании")
    query.prepare("SELECT id, name, description FROM companies");
  }
  else if (nextLevel == 1) {
    // Уровень 1: Дочерние элементы (например, "Департаменты", привязанные к id компании)
    query.prepare("SELECT id, name, code FROM departments WHERE company_id = :parent_id");
    query.bindValue(":parent_id", item->id());
  }
  else if (nextLevel == 2) {
    // Уровень 2: Следующий уровень (например, "Сотрудники", привязанные к id департамента)
    query.prepare("SELECT id, last_name, position FROM employees WHERE department_id = :parent_id");
    query.bindValue(":parent_id", item->id());
  }
  else {
    return; // Максимальная глубина достигнута
  }

  if (!query.exec()) {
    qWarning() << "SQL error:" << query.lastError().text();
    return;
  }

  // Сообщаем модели, что собираемся вставить строки (для корректной работы TreeView)
  // Так как это ленивая загрузка внутри index()/rowCount(), вызываем методы аккуратно
  while (query.next()) {
    int id = query.value(0).toInt();
    QVector<QVariant> data = { query.value(1), query.value(2) };

    TreeItem *child = new TreeItem(data, id, nextLevel, item);
    item->appendChild(child);
  }
}
