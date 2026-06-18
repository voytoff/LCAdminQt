#include "moduleview.h"
#include "ui_moduleview.h"

ModuleView::ModuleView(QWidget *parent)
  : QScrollArea(parent)
  , ui(new Ui::ModuleView)
{
  ui->setupUi(this);
}

ModuleView::~ModuleView()
{
  delete ui;
}
