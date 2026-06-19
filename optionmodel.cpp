#include "optionmodel.h"

OptionModel::OptionModel(DB *db, const QVariantList &headers, const QStringList icons, QObject *parent)
  : ModelTreeBase(db, headers, icons, parent) {}

void OptionModel::loadChildren(TreeItem *parentItem) const {
  // Приведение к неконстантному указателю для изменения флага и добавления детей
  TreeItem *item = const_cast<TreeItem*>(parentItem);
  item->setLoaded(true);

  int nextLevel = item->level() + 1;

  // В зависимости от уровня строим соответствующий SQL-запрос
  if (nextLevel == 0) {
    // Уровень 0: Крейты
    foreach (dbCrate *i, db->crates()) {
      TreeItem *child = new TreeItem({ i->name }, i->id, nextLevel, item);
      item->appendChild(child);
    }
  }
  else if (nextLevel == 1) {
    // Уровень 1: LTR-Модули
    foreach (dbModule *i, db->modules(item->id())) {
      TreeItem *child = new TreeItem({ i->name }, i->id, nextLevel, item);
      item->appendChild(child);
    }
  }
  else {
    qDebug() << "Максимальная глубина достигнута";
  }
}
