#include "dictionmodel.h"

DictionModel::DictionModel(DB *db, const QVariantList &headers, const QStringList icons, QObject *parent)
  : ModelTreeBase(db, headers, icons, parent) {}

TreeItemType DictionModel::get(const int &row) const {
  if (row < defs.count()) return defs.at(row);
  return {};
}

QVariant DictionModel::get(const int &row, const int &column) const {
  if (row < defs.count() && column < TreeItemType::length())
    return defs.at(row).at(column);
  return QVariant();
}

QVariant DictionModel::getIcon(const QModelIndex &index, TreeItem *item) const {
  if (index.column() == 0)
    return QIcon(item->data(1).toString());
  return QVariant();
}

void DictionModel::loadChildren(TreeItem *parentItem) const {
  // Приведение к неконстантному указателю для изменения флага и добавления детей
  TreeItem *item = const_cast<TreeItem*>(parentItem);
  item->setLoaded(true);

  int nextLevel = item->level() + 1;

  // В зависимости от уровня строим соответствующий SQL-запрос
  if (nextLevel == 0) {
    // Уровень 0: Крейты
    foreach (auto table, defs) {
      TreeItem *child = new TreeItem({table.title, table.icon}, table.type, nextLevel, item);
      item->appendChild(child);
    }
  }
  else {
    qDebug() << "Максимальная глубина достигнута";
  }
}
