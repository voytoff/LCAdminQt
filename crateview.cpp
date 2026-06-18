#include "crateview.h"
#include "ui_crateview.h"

CrateView::CrateView(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::CrateView)
{
  ui->setupUi(this);
}

CrateView::~CrateView()
{
  delete ui;
}
