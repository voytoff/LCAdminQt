#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow{parent}
  , schemeHelper(new SchemeHelper(this, ":/images/admin.svg"))
  , settings(new Settings())
  , db(new DB()) {

  QIcon::setThemeName("Material Symbols Outlined");

  createActions();
  createControlBar();
  statusBar()->setSizeGripEnabled(true);
  schemeHelper->applayColorScheme(settings->colorScheme(), true);
  if (!db->open())
    QMessageBox::critical(this, AppName, db->lastError().text());

  restoreLayout();
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

void MainWindow::closeEvent(QCloseEvent *event) {
  saveLayout();
  QMainWindow::closeEvent(event);
}

void MainWindow::saveLayout() {
  settings->geometry(saveGeometry());
  settings->windowState(saveState());
  //settings->splitter(splitter->saveState());
}

void MainWindow::restoreLayout() {
  restoreGeometry(settings->geometry());
  restoreState(settings->windowState());
  //splitter->restoreState(settings->splitter());
}
