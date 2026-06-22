#include "tableview.h"
#include "mainwindow.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QString>
#include <QCloseEvent>

TableView::TableView(ModelTableBase *model, const QString &title, QWidget *parent)
  : QTableView{parent}
  , model(model)
  , name(title) {

  verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  verticalHeader()->setDefaultSectionSize(22); // pixels
  setModel(model);
  int id = index("id");
  if (id > -1) // Скрываем id столбец
    setColumnHidden(id, true);
  resizeColumnsToContents();
}

int TableView::index(const QString &fieldName) const {
  return model->fieldIndex(fieldName);
}

bool TableView::isModified() const {
  return model->isDirty();
}

bool TableView::save() {
  return model->submitAll();
}

void TableView::cancel() {
  model->revertAll();
}

void TableView::closeEvent(QCloseEvent *event) {
  if (isModified()) {
    auto response = QMessageBox::question(MainWindow::getInstance(), title, QString("Данные таблицы '%1' изменены. Сохранить эти изменения?").arg(name), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (response == QMessageBox::Yes)
      save();
    else if (response == QMessageBox::Cancel) {
      event->ignore();
      return;
    }
  }
  event->accept();
}
