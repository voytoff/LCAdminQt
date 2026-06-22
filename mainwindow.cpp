#include "mainwindow.h"
#include "crateview.h"
#include "leftview.h"
#include "modeltablebase.h"
#include "moduleview.h"
#include "settingsdlg.h"
#include "tableview.h"
#include "types.h"

#include <QSqlRelationalDelegate>
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

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow{parent}
  , schemeHelper(new SchemeHelper(this, ":/images/admin.png"))
  , settings(new Settings(this))
  , db(new DB(settings->hostName(), settings->hostPort(), settings->databaseName(), settings->userName(), settings->password(), settings->timeout(), this))
  , optionView(new TreeView("Установки", this))
  , dictionView(new TreeView("Справочник", this))
  , tabView(new TabView(this))
  , splitter(new QSplitter(this))
  , toolbar(addToolBar("Главный")) {

  instance = this;

  leftView = new LeftView(dictionView, optionView);

  setWindowTitle(title);
  createActions();
  createControlBar();
  statusBar()->setSizeGripEnabled(true);
  createControlBox();

  restoreLayout();
}

MainWindow* MainWindow::getInstance() {
  return instance;
}

void MainWindow::createActions() {
  openAction = schemeHelper->create(tr("Открыть..."), ":/images/tb/open.png", QKeySequence::Open);
  saveAction = schemeHelper->create(tr("Сохранить"), ":/images/tb/save.png", QKeySequence::Save);
  lightAction = schemeHelper->createLightAction(tr("Дневной режим"), ":/images/tb/light.svg");
  darkAction = schemeHelper->createDarkAction(tr("Ночной режим"), ":/images/tb/dark.svg");
  settingsAction = schemeHelper->create(tr("Установки..."), ":/images/tb/settings.png");
  addAction = schemeHelper->create(tr("Добавить..."), ":/images/tb/add.png", QKeySequence::InsertLineSeparator);
  delAction = schemeHelper->create(tr("Удалить"), ":/images/tb/del.png", QKeySequence::Delete);
  toggleOptionAction = leftView->toggleOptionAction();
  toggleDictionAction = leftView->toggleDictionAction();

  connect(settingsAction, &QAction::triggered, this, &MainWindow::doSettings);
  connect(addAction, &QAction::triggered, this, &MainWindow::add);
  connect(delAction, &QAction::triggered, this, &MainWindow::del);

  schemeHelper->applayColorScheme(settings->colorScheme(), true);
}

void MainWindow::createControlBar() {
  QMenu *fileMenu = menuBar()->addMenu(tr("Файл"));
  fileMenu->addAction(openAction);
  fileMenu->addAction(saveAction);

  QMenu *viewMenu = menuBar()->addMenu(tr("Вид"));
  viewMenu->addAction(lightAction);
  viewMenu->addAction(darkAction);
  viewMenu->addSeparator();
  viewMenu->addAction(toggleOptionAction);
  viewMenu->addAction(toggleDictionAction);

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
  //connect(treeView, &QTreeView::doubleClicked, this, &MainWindow::editSensor);
  //сonnect(optionView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::reload);

  //tabView->setTabsClosable(true);
  //connect(tabView, &QTabWidget::tabCloseRequested, this, [this](int index) {
  //  QWidget* w = tabView->widget(index);
  //  tabView->removeTab(index);
  //  delete w;
  //});

  splitter->addWidget(leftView);
  splitter->addWidget(tabView);

  QGridLayout *layout = new QGridLayout();
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

void MainWindow::restoreLayout() {
  restoreGeometry(settings->geometry());
  restoreState(settings->windowState());
  splitter->restoreState(settings->splitter());
  leftView->restoreState(settings->splitter2());
}

void MainWindow::saveLayout() {
  settings->geometry(saveGeometry());
  settings->windowState(saveState());
  settings->splitter(splitter->saveState());
  settings->splitter2(leftView->saveState());
  //settings->colorScheme(schemeHelper->colorScheme());
}

void MainWindow::loadData() {
  optionView->setModel(nullptr);
  if (db->open()) {
    optionView->setModel(optionModel = new OptionModel(db, {"Название", "Инфо"}, {icon_crate, ":/images/db/table.png"}, this));
    dictionView->setModel(dictionModel = new DictionModel(db, {"Название"}, {icon_crate, icon_module}, this));
    dictionView->setHeaderHidden(true);
    //connect(optionView, &QTreeView::doubleClicked, this, &MainWindow::openTable);
    connect(dictionView, &QTreeView::doubleClicked, this, &MainWindow::openTable);
  } else {
    showMessage(db->lastError().text());
    QMessageBox::critical(this, title, db->lastError().text());
  }
}

void MainWindow::add() {
  auto w = new CrateView(this);
  tabView->append(w, "тест 1", documentType::crate, 1000);
}

void MainWindow::del() {
  auto w = new ModuleView(this);
  tabView->append(w, "тест 2", documentType::module, 99);
}

void MainWindow::doSettings() {
  SettingsDlg *dialog = new SettingsDlg(settings, this);
  int accepted = dialog->exec();
  if (accepted == QDialog::Accepted) {
    auto colorScheme = settings->colorScheme();
    if ((Qt::ColorScheme)colorScheme != QGuiApplication::styleHints()->colorScheme())
      schemeHelper->applayColorScheme(colorScheme);
    tabView->closeAll();
    db->close();
    delete db;
    db = new DB(settings->hostName(), settings->hostPort(), settings->databaseName(), settings->userName(), settings->password(), settings->timeout());
    loadData();
  }
}

void MainWindow::openTable(const QModelIndex &index) {
  if (index.isValid()) {
    auto data = dictionModel->get(index.row());
    ModelTableBase *model = ModelTableBase::create(data.type, data.table);
    if (model) {
      TableView *tableView = new TableView(model, data.title, this);
      tabView->append(tableView, data.title, data.type, data.type, data.icon);
      //model->select();
      tableView->setItemDelegate(new QSqlRelationalDelegate(tableView));
    }
  }
}

