#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow{parent}
  , schemeHelper(new SchemeHelper(this, ":/images/admin.svg"))
  , settings(new Settings()) {

  QIcon::setThemeName("Material Symbols Outlined");

  createActions();
  createControlBar();
  statusBar()->setSizeGripEnabled(true);
  schemeHelper->applayColorScheme(settings->colorScheme(), true);
}


void MainWindow::createActions() {
  lightAction = schemeHelper->createLightAction(tr("Дневной режим"), ":/images/tb/light.svg");
  darkAction = schemeHelper->createDarkAction(tr("Ночной режим"), ":/images/tb/dark.svg");
}



void MainWindow::createControlBar() {
  QMenu *viewMenu = menuBar()->addMenu(tr("Вид"));
  viewMenu->addAction(lightAction);
  viewMenu->addAction(darkAction);

}

