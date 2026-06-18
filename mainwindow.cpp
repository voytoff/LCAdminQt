#include "mainwindow.h"
#include "settingsdlg.h"
#include "sqltreemodel.h"

#include <QGuiApplication>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QGridLayout>
#include <QStyleHints>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow{parent}
  , schemeHelper(new SchemeHelper(this, ":/images/admin.png"))
  , settings(new Settings())
  , db(new DB(settings->hostName(), settings->hostPort(), settings->databaseName(), settings->userName(), settings->password(), settings->timeout()))
  , treeView(new TreeView(settings, this))
  , tabView(new QTabWidget(this))
  , splitter(new QSplitter(this))
  , toolbar(addToolBar("Главный")) {

  setWindowTitle(title);

  createActions();
  createControlBar();
  statusBar()->setSizeGripEnabled(true);
  createControlBox();

  //connect(timer, &QTimer::timeout, this, [this]() {statusBar()->showMessage(ready);});

  restoreLayout();
}

void MainWindow::createActions() {
  openAction = schemeHelper->create(tr("Открыть..."), ":/images/tb/open.png", QKeySequence::Open);
  saveAction = schemeHelper->create(tr("Сохранить"), ":/images/tb/save.png", QKeySequence::Save);
  lightAction = schemeHelper->createLightAction(tr("Дневной режим"), ":/images/tb/light.svg");
  darkAction = schemeHelper->createDarkAction(tr("Ночной режим"), ":/images/tb/dark.svg");
  settingsAction = schemeHelper->create(tr("Установки..."), ":/images/tb/settings.png");
  addAction = schemeHelper->create(tr("Добавить..."), ":/images/tb/add.png", QKeySequence::InsertLineSeparator);
  delAction = schemeHelper->create(tr("Удалить"), ":/images/tb/del.png", QKeySequence::Delete);

  connect(settingsAction, &QAction::triggered, this, &MainWindow::doSettings);

  schemeHelper->applayColorScheme(settings->colorScheme(), true);
}

void MainWindow::createControlBar() {
  QMenu *fileMenu = menuBar()->addMenu(tr("Файл"));
  fileMenu->addAction(openAction);
  fileMenu->addAction(saveAction);

  QMenu *viewMenu = menuBar()->addMenu(tr("Вид"));
  viewMenu->addAction(lightAction);
  viewMenu->addAction(darkAction);

  QMenu *toolMenu = menuBar()->addMenu(tr("Инструменты"));
  toolMenu->addAction(settingsAction);

  schemeHelper->setupToolbar(toolbar);
  toolbar->setObjectName("General");
  toolbar->addAction(openAction);
  toolbar->addAction(saveAction);
  toolbar->addSeparator();
  toolbar->addAction(addAction);
  toolbar->addAction(delAction);
  toolbar->addSeparator();
  toolbar->addAction(settingsAction);
}

void MainWindow::createControlBox() {
  //treeView->setModel(model);
  //connect(treeView, &QTreeView::doubleClicked, this, &MainWindow::editSensor);
  connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::reload);

  tabView->setTabsClosable(true);
  connect(tabView, &QTabWidget::tabCloseRequested, this, [this](int index) {
    QWidget* w = tabView->widget(index);
    tabView->removeTab(index);
    delete w;
  });

  splitter->addWidget(treeView);
  splitter->addWidget(tabView);

  QGridLayout *layout = new QGridLayout;
  layout->addWidget(splitter, 0, 0);
  layout->setContentsMargins(2, 1, 2, 0);

  QWidget *widget = new QWidget;
  widget->setLayout(layout);
  setCentralWidget(widget);
}

void MainWindow::closeEvent(QCloseEvent *event) {
  saveLayout();
  QMainWindow::closeEvent(event);
}

void MainWindow::showEvent(QShowEvent *event) {
  QTimer::singleShot(200, this, [this]() {
    loadData();
  });
}

void MainWindow::showMessage(const QString &text) {
  statusBar()->showMessage(text);
  QTimer::singleShot(readyTimeout, this, [this]() {
    statusBar()->showMessage(ready);
  });
}

void MainWindow::saveLayout() {
  settings->geometry(saveGeometry());
  settings->windowState(saveState());
  settings->splitter(splitter->saveState());
}

void MainWindow::loadData() {
  treeView->setModel(nullptr);
  if (db->open()) {
    auto model = new SqlTreeModel(db, this);
    treeView->setModel(model);
  } else {
    showMessage(db->lastError().text());
    QMessageBox::critical(this, title, db->lastError().text());
  }
}

void MainWindow::reload() {
  //showMessage(treeView->selectionModel()->selection().)
}

void MainWindow::doSettings() {
  SettingsDlg *dialog = new SettingsDlg(settings, this);
  int accepted = dialog->exec();
  if (accepted == QDialog::Accepted) {
    auto colorScheme = settings->colorScheme();
    if ((Qt::ColorScheme)colorScheme != QGuiApplication::styleHints()->colorScheme())
      schemeHelper->applayColorScheme(colorScheme);
    db->close();
    delete db;
    db = new DB(settings->hostName(), settings->hostPort(), settings->databaseName(), settings->userName(), settings->password(), settings->timeout());
    loadData();
  }
}

void MainWindow::restoreLayout() {
  restoreGeometry(settings->geometry());
  restoreState(settings->windowState());
  splitter->restoreState(settings->splitter());
}

