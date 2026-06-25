#include "sqlcombobox.h"
#include "DBExtension_global.h"
#include "db.h"
#include <QSqlQuery>

SqlComboBox::SqlComboBox(const QString &query, QWidget *parent)
  : QComboBox{parent}
  , query(query) {}

bool SqlComboBox::setCurrentData(const QVariant &data) {
  int index = findData(data);
  if (index > -1) setCurrentIndex(index);
  return index > -1;
}

void SqlComboBox::showPopup() {
  // Очищаем старые данные
  auto value = currentData();
  clear();
  addItem(nullptr, 0);
  // Добавляем новые данные (например, из базы данных или сети)
  QSqlQuery q(query, DB::instance(DatabaseName));
  while (q.next()) {
    int id = q.value("id").toInt();
    QString name = q.value("name").toString();
    addItem(name, id);
  }
  setCurrentData(value);
  // Вызываем базовый метод, чтобы список корректно открылся
  QComboBox::showPopup();
}