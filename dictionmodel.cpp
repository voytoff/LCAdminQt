#include "dictionmodel.h"

DictionModel::DictionModel(DB *db, const QVariantList &headers, const QStringList icons, QObject *parent)
  : ModelTreeBase(db, headers, icons, parent) {}

QVariant DictionModel::get(const int &row, const int &column) const {
  if (row < defs.count() && column < defs.at(0).length())
    return defs.at(row).at(column);
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
      TreeItem *child = new TreeItem({table.at(1)}, table.at(0).toInt(), nextLevel, item);
      item->appendChild(child);
    }
  }
  //else if (nextLevel == 1) {
  //  // Уровень 1: LTR-Модули
  //  foreach (dbModule *i, db->modules(item->id())) {
  //    TreeItem *child = new TreeItem({ i->name }, i->id, nextLevel, item);
  //    item->appendChild(child);
  //  }
  //}
  else {
    qDebug() << "Максимальная глубина достигнута";
  }
}
