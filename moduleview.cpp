#include "moduleview.h"
#include "ui_moduleview.h"

ModuleView::ModuleView(QWidget *parent)
  : QDockWidget(parent)
  , ui(new Ui::ModuleView)
{
  ui->setupUi(this);
}

ModuleView::~ModuleView()
{
  delete ui;
}
