#include "tableview.h"
#include <QHeaderView>

TableView::TableView(ModelTableBase *model, QWidget *parent)
  : QTableView{parent} {

  verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  verticalHeader()->setDefaultSectionSize(22); // pixels
  setModel(model);
  setColumnHidden(0, true); // Скрывает id столбец
}
