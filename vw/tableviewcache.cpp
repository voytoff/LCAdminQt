#include "tableviewcache.h"
#include "../mainwindow.h"
#include <QApplication>
#include <QSqlError>
#include <QMessageBox>

TableViewCache::TableViewCache()
  : QHash<Enums::documentType, TableView*>() {}

bool TableViewCache::isModified() const {
  foreach (auto t, this->values())
  if (t->model()->isDirty())
    return true;
  return false;
}

bool TableViewCache::save() {
  bool result = true;
  QStringList errors;
  foreach (auto t, this->values()) {
    auto model = t->model();
    if (model->isDirty()) {
      bool success = model->submitAll();
      if (!success) {
        errors << model->lastError().text();
        qDebug() << model->lastError();
        result = false;
      }
    }
  }
  if (!result)
    QMessageBox::critical(MainWindow::mw(), title, errors.join("\n"));
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
