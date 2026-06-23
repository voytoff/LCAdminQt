#include "tableview.h"
#include "mainwindow.h"
#include "types.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QString>
#include <QCloseEvent>

TableView::TableView(ModelTableBase *model, const QString &title, QWidget *parent)
  : QTableView{parent}
  //, model(model)
  , title(title) {

  setModel(model);
  // Устанавливаем делегаты пользовательских редакторов
  model->setItemDelegates(this);
  // Внешний вид
  verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  verticalHeader()->setDefaultSectionSize(22); // pixels
  int id = index("id");
  if (id > -1) // Скрываем id столбец
    setColumnHidden(id, true);
  horizontalHeader()->setMinimumSectionSize(minColumnSize);
  resizeColumnsToContents();
}

int TableView::index(const QString &fieldName) const {
  return model()->fieldIndex(fieldName);
}

bool TableView::isModified() const {
  return model()->isDirty();
}

bool TableView::save() {
  return model()->submitAll();
}

void TableView::cancel() {
  model()->revertAll();
}

void TableView::closeEvent(QCloseEvent *event) {
  if (isModified()) {
    auto response = QMessageBox::question(qobject_cast<MainWindow*>(parent()), title, QString("Данные таблицы '%1' изменены. Сохранить эти изменения?").arg(title), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (response == QMessageBox::Yes)
      save();
    else if (response == QMessageBox::Cancel) {
      event->ignore();
      return;
    }
  }
  event->accept();
}
