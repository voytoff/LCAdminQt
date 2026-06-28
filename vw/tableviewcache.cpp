#include "tableviewcache.h"
#include <QApplication>

TableViewCache::TableViewCache()
  : QHash<Enums::documentType, TableView*>() {}

bool TableViewCache::isModified() const {
  foreach (auto t, this->values())
  if (t->model()->isDirty())
    return true;
  return false;
}

bool TableViewCache::save() {
  bool result = false;
  foreach (auto t, this->values()) {
    if (t->model()->isDirty()) {
      result = true;
      t->model()->submitAll();
    }
  }
  return result;
}

void TableViewCache::cancel() {
  foreach (auto t, this->values())
    if (t->model()->isDirty())
      t->model()->revertAll();
}

void TableViewCache::clear() {
  auto t = qobject_cast<TableView*>(QApplication::focusWidget());
  if (t) t->clear();
}

TableView *TableViewCache::first() {
  return count() > 0 ? values().at(0) : nullptr;
}
