#include "tableview.h"
#include <QHeaderView>

TableView::TableView(ModelTableBase *model, QWidget *parent)
  : QTableView{parent}
  , model(model) {

  verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  verticalHeader()->setDefaultSectionSize(22); // pixels
  setModel(model);
  int id = index("id");
  if (id >= 0) // Скрываем id столбец
    setColumnHidden(id, true);
}

int TableView::index(const QString &fieldName) const {
  return model->fieldIndex(fieldName);
}
